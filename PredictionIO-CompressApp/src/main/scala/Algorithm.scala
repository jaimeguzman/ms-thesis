package cl.jguzman.piocompressapp

import io.prediction.controller.{Params, P2LAlgorithm,PersistentModel,PersistentModelLoader,EmptyEvaluationInfo}

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
    //println("\n.... Training .....\n")

    require(!data.labeledPoints.take(1).isEmpty,
      s"RDD[WebAccess]  PreparedData no puede estar vacio." +
        " Verificar si  DataSource genera TrainingData" +
        " y Preprator genera PreparedData correctamente.")

    val webaccessLoad: RDD[WebAccess] = data.labeledPoints
    val trie = lztrie.trie

    val lastUserWebAccess = webaccessLoad.takeOrdered(1)(Ordering[Int].reverse.on(_.user.get) ).toList.head.user.get
    val webaccessMap      = webaccessLoad.map( x => List(x.user,x.page )  ).collect()
    val webaccessGrouped  = webaccessMap.groupBy(_.head).toList


    /**
     * TEST
     * INPUT:  “A A A B A B B B B B A A B C C D D C B A A A A”
     * OUTPUT: “A,AA,B,AB,BB,BBA,ABC,C,D,DC,BA,AAA”.
     *
     * 	A	AA	AB	ABB	B	BB	AAB	C	CD	D	CB	AAA

     * */

    //For checking if the trie is constructed well


    /*  trie.append("A" )
      trie.append("AA" )
      trie.append("B" )
      trie.append("AB" )
      trie.append("BB" )
      trie.append("BBA" )
      trie.append("ABC" )
      trie.append("C" )
      trie.append("D" )
      trie.append("D" )
      trie.append("DC" )
      trie.append("BA" )
      trie.append("AAA" )
     */


    // this is for iterate all the session of all the users
    for( wg   <- webaccessGrouped  ){

      val user_session  = Stack[String]()
      val num_pages     = wg._2.length
      val dictionary    = Stack[String]()
      var phrase:String = ""

      // Restore the user session from RDD
      for (i <- 0 until num_pages ) {
        val c = wg._2.apply(i).last.get.asInstanceOf[String]
        user_session.push(c)
        phrase += c
      }


      val phraseCharArray = phrase.toCharArray

      // Add the root symbol
      if( phrase.length >0 ) dictionary.push( phraseCharArray(0).toString  )



      // Here is the Lempel Ziv 78 algorithm
      var w:String =""

      for( x <- 0 until phraseCharArray.length   ){
        val ch = phraseCharArray(x)
        w = w.concat(ch.toString)

        if( ! dictionary.contains( w )  ){
          dictionary.push(  w  )
          w=""
        }


      }


      // Add to the trie
      for(   r <- dictionary.reverse   )  trie.append(r) //print ("\t"+ r )


    }



    /*

    // Read each session from users on EventServer
    for (it <- webaccessGrouped) {


      val userSession = Stack[String]()
      val sizeOfTrieMap = it._2.length

      // This is a temporal stack to
      for (i <- 0 until sizeOfTrieMap) userSession.push(it._2.apply(i).last.get.asInstanceOf[String])

      val userSessionReverse= userSession.reverse


      breakable {
        for( j <- 0 to userSessionReverse.size - 1) {
          // print(".")
          var pattern = userSessionReverse(j)

          if( pattern!="" && trie.contains( pattern ) && (j+1) < userSession.size ){

              pattern = pattern.concat(userSessionReverse(j+1) )
              var patternAux = pattern //this var see two symbols
              trie.append( pattern )

              /*
                j+1
                pattern = pattern.concat(userSessionReverse(j+1) )
                //new patter move more
                //  println("::::::::::::: pattern.startsWith(patternAux) \t"+pattern.startsWith(patternAux) )
                if( !trie.contains(pattern)  && pattern.startsWith(patternAux)   ){
                //    println("\t\t\t\t>>>>>\t MATCH con j+2 \t "+ pattern)
                  trie.append( pattern )
                  pattern =""
                  userSessionReverse(j+1)= ""

              }*/
              pattern =""
              userSessionReverse(j+1)= ""

          }else{
              trie.append( pattern )
              pattern =""
          }
        }
      }
    }
    */




   // trie.printTree( t => print( t ) ); println();

    new LZModel(trie)
  }




  def predict(model: LZModel, query: Query): PredictedResult = {
    val lzResult =      lztrie.trie

    lzResult.printTree( t => print( t ) ); println();
    lzResult.numberOfNodes()
    lzResult.printHeigthTrieNode(h => print(h)); println();

    new PredictedResult( lzResult.predictNextPage( query.webaccess ) )

  }









}