package cl.jguzman.piocompressapp



import scala.collection.JavaConversions._



import io.prediction.controller.{Params, P2LAlgorithm,PersistentModel}
import org.apache.spark.SparkContext


import org.apache.spark.mllib.tree.impurity.{Variance, Entropy, Gini, Impurity}
import org.apache.spark.mllib.tree.configuration.Algo._

import scala.util.Random

import grizzled.slf4j.Logger

import io.prediction.controller.PersistentModel

import cl.jguzman.piocompressapp.trie._

import scala.math.Ordering.Implicits._


/***
 * Parametros que le estoy pasando al algoritmo
 * Estos se pueden ir declarando en el engine.json adicionalmente
 **/
case class AlgorithmParams(
  numAlphabet: Integer
) extends Params



 class LZModel(
     val sc: SparkContext

     ) extends PersistentModel[AlgorithmParams] with Serializable {

    @transient lazy val logger = Logger[this.type]
    def save(id: String, params: AlgorithmParams, sc: SparkContext): Boolean = {

      false

      }

  }



 class Algorithm(val ap: AlgorithmParams)
  extends P2LAlgorithm [PreparedData,
                        LZModel,
                        Query,
                        PredictedResult] {

  @transient lazy val logger = Logger[this.type]



  def train(sc: SparkContext ,   data: PreparedData): LZModel = {

    require(!data.labeledPoints.take(1).isEmpty,
      s"RDD[WebAccess]  PreparedData no puede estar vacio." +
        " Verificar si  DataSource genera TrainingData" +
        " y Preprator genera PreparedData correctamente.")


    System.out.print( "Exsiten muchos puntos que quiero ivnestigar con los RDD" )

    println("\n\n\n")
    val rows  = data.labeledPoints

    println( "la clase de data es.::::" +   data.getClass )
    println(data.labeledPoints.take(1).isEmpty  )
    println(data.labeledPoints.take(1)  )
    println(data.labeledPoints.count()  )
    println(data.labeledPoints.first()  )
//    println(data.labeledPoints.toDebugString)
  //  println(data.labeledPoints.toString() )



    //rows.collect().foreach(a => println(a.toString() ))

    val trie = new TrieNode()


    //data.labeledPoints.sortBy( c => c.user.get   ,true)

    val lastUserWebAccess = data.labeledPoints.takeOrdered(1)(Ordering[Int].reverse.on(_.user.get) ).toList.head.user.get

    System.out.println(":::::::::::el ultimo "+   lastUserWebAccess  )



    // num de usuarios como parametro del algoritmo


    System.out.println("*********" + data.labeledPoints.collect().apply(8).user.get  );


    /*
    for( j <- 0 until  data.labeledPoints.count().toInt ){
        println("j :"+j+"   "+  data.labeledPoints.collect().apply( j ).user.get   )
    }*/



    val test = data.labeledPoints.map( x => List(x.user,x.page )  ).collect()
    val test2 = test groupBy(_.head) toList //.sortBy( _._2.toList. )

    //test2.sortBy( a => a._1.head    )(Ordering[Any].reverse)





    for( it <- test2){
      //      println(  it._1.head  );
      print (  it._1.head +"\t "+"# "+it._2.length+"\t")

           for(  i <- 0 until  it._2.length ){

                  print(" "+ it._2.apply(i).last.get )

           }
      println()




    }

    val tmp: List[String] = Nil

    /*
    for( i <- 0 to lastUserWebAccess){

          if( i.equals( test.apply(i).head.get )  ){

              println( "es igual "+i+"   "+test.apply(i).head.get  );
          }else{

            println( "NO es igual "+i+"   "+test.apply(i).head.get  );
          }
    }*/



    println(  test.apply( 10  ).tail  )












       new LZModel(sc)





  }








   /**El predictor es la lectura del TRIE LZ ***/

  def predict(model: LZModel, query: Query): PredictedResult = {








    new PredictedResult( 2.0 )

  }



}