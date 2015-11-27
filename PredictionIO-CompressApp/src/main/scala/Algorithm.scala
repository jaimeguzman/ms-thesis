package cl.jguzman.piocompressapp

import io.prediction.controller.{Params, P2LAlgorithm,PersistentModel,PersistentModelLoader}
import org.apache.spark.mllib.tree.impurity.{Variance, Entropy, Gini, Impurity}
import grizzled.slf4j.Logger
import scala.collection.mutable.Stack
import scala.util.control.Breaks._
import scala.util.Random

import org.apache.spark.rdd.RDD
import org.apache.spark.SparkContext
import org.apache.spark.sql.{SQLContext, SchemaRDD}


import org.apache.spark.sql._

/***
 * Parametros que le estoy pasando al algoritmo
 * Estos se pueden ir declarando en el engine.json adicionalmente
 **/
case class AlgorithmParams(
  numAlphabet: Integer
) extends Params



class LZModel(
      val lz: TrieNode) extends PersistentModel[AlgorithmParams]
          with Serializable{

   @transient lazy val logger = Logger[this.type]
   def save(id: String, params: AlgorithmParams, sc: SparkContext): Boolean = {
     //println(" ::::::: ENTRO A SAVE ::::::::::: ")

     val sqlContext = new SQLContext(sc)
     import sqlContext._

     // Create an RDD
     val lzmodel = sc.textFile("data/lzmodel.txt")



     // Import Row.
     import org.apache.spark.sql.Row

     // Import Spark SQL data types
     //import org.apache.spark.sql.types.{StructType,StructField,StringType}

     // The schema is encoded in a string
     val schemaString = "uid page pos prob"


     // Generate the schema based on the string of schema
     /*   val schema =
       StructType(
         schemaString.split(" ").map(fieldName => StructField(fieldName, StringType, true))
       )
      */


     false

   }
}

object lztrie{
  val trie = new TrieNode()
}


object LZModel extends PersistentModelLoader[AlgorithmParams, LZModel]{
  def apply(id: String, params: AlgorithmParams, sc: Option[SparkContext]):LZModel=
    {

      new LZModel(lztrie.trie)
    }
}







class Algorithm(val ap: AlgorithmParams)
  extends P2LAlgorithm [PreparedData,
                        LZModel,
                        Query,
                        PredictedResult] {
  @transient lazy val logger = Logger[this.type]



  def train(sc: SparkContext ,   data: PreparedData): LZModel = {
    println("\n\n\n.... Training .....\n")

    require(!data.labeledPoints.take(1).isEmpty,
      s"RDD[WebAccess]  PreparedData no puede estar vacio." +
        " Verificar si  DataSource genera TrainingData" +
        " y Preprator genera PreparedData correctamente.")

    val webaccessLoad: RDD[WebAccess] = data.labeledPoints



    val trie = lztrie.trie

    val lastUserWebAccess = webaccessLoad.takeOrdered(1)(Ordering[Int].reverse.on(_.user.get) ).toList.head.user.get
    //System.out.println(":::::::::::lastUserWebAccess\t "+   lastUserWebAccess  )


    val test = webaccessLoad.map( x => List(x.user,x.page )  ).collect()

    val test2 = test.groupBy(_.head).toList
    test2.sortBy( _._1.get.asInstanceOf[Int] )


    for( it <- test2){
           val userSession =  Stack[String]()
           for(  i <- 0 until  it._2.length ){
             userSession.push( it._2.apply(i).last.get.asInstanceOf[String] )
             //print(" "+ it._2.apply(i).last.get.asInstanceOf[String] ) // La idea es aqui ir agregando al mdoelo geerado
           }
           print("\t  Lista de tamaño temporal "+ userSession.length +"\n")


          for(  j <- 0 until  it._2.length ){

            var tmpStr = ""
            breakable {
              for (j <- 0 to userSession.size - 1) {
                //print ( ":: j ::\t" + j +"\t\t" + "X es: " + userSession.apply(j) +"\t\t")

                if (trie.contains(userSession(j)) == true) {
                 // print("esta en el diccionario y userSession(j) es: " + userSession(j) )
                  //Thread sleep  500

                  //stop looking forward to avoid overflow
                  if ((j + 2) >= userSession.size) {
                    //println("\t\t\t"+"value de j+2 es\t" + (j + 2))
                    break
                  }
                  //Aca puedo ir concatennando all lo que vea en el futuro
                  tmpStr += userSession.apply(j).concat(userSession.apply(j+1)).concat(userSession.apply(j+2)) //+ userSession(i + 1)
                  //println("tmpStr " + tmpStr)
                  if (tmpStr.length > 1) trie.append(tmpStr)

                  //reset tmp
                  tmpStr = ""

                } else {
                  trie.append(userSession(j))
                  tmpStr = ""
                }
                //println()
              }
            }
          }
    }
    //    trie.printTree( t => print( t ) )
    //    println(  )

    new LZModel(trie)
  }








   /**El predictor es la lectura del TRIE LZ ***/

  def predict(model: LZModel, query: Query): PredictedResult = {

      val tester = model.lz.findByPrefix("AF")

     println("la ruta hasta AF es :\t"+tester )
     print( "EL modelo LZ cargado es:\t" )
     println( model.lz.toString() )
     println(query )



     lztrie.trie.printTree( t => print( t ) )
     println(  )

      for( t <- tester){
          println(t)
      }



    new PredictedResult( 2.0 )

  }



}