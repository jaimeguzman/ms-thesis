package org.template.classification
import scala.collection.JavaConverters._
import scala.collection.JavaConversions._
import org.apache.spark.SparkContext

import io.prediction.controller.P2LAlgorithm
import io.prediction.controller.Params

import org.apache.spark.mllib.linalg.Vectors

import org.apache.spark.mllib.tree.DecisionTree
import org.apache.spark.mllib.tree.model.DecisionTreeModel
import org.apache.spark.mllib.tree.configuration.Algo
import org.apache.spark.mllib.tree.configuration.Strategy


import org.apache.spark.mllib.tree.impurity.{Variance, Entropy, Gini, Impurity}
import org.apache.spark.mllib.tree.configuration.Algo._

import org.apache.spark.mllib.util.MLUtils

import grizzled.slf4j.Logger

/**
 * @TODO: Migrar a LempelZiv SRC file
 */


case class LempelZivAlgorithmParams(
  
  numPages: Integer

) extends Params


class LempelZivAlgorithmModel(
      val user:           Int,
      val userFeatures:   Int, //Map[Int, Array[Int]],
      val userPredictio:  Int
      ) extends Serializable {
  /*
  @transient lazy val itemIntStringMap = itemStringIntMap.inverse

  override def toString = {
    s" rank: ${rank}" +
      s" userFeatures: [${userFeatures.size}]" +
      s"(${userFeatures.take(2).toList}...)" +
      s" productFeatures: [${productFeatures.size}]" +
      s"(${productFeatures.take(2).toList}...)" +
      s" userStringIntMap: [${userStringIntMap.size}]" +
      s"(${userStringIntMap.take(2).toString}...)]" +
      s" itemStringIntMap: [${itemStringIntMap.size}]" +
      s"(${itemStringIntMap.take(2).toString}...)]"
  }
  */
}




// extends P2LAlgorithm because the MLlib's NaiveBayesModel doesn't contain RDD.
class Algorithm(val ap: LempelZivAlgorithmParams)
  extends P2LAlgorithm[PreparedData, LempelZivAlgorithmModel, Query, PredictedResult] {

  @transient lazy val logger = Logger[this.type]

  def train(sc: SparkContext,data: PreparedData): LempelZivAlgorithmModel = {
    // MLLib DecisionTree cannot handle empty training data.
    require(!data.labeledPoints.take(1).isEmpty,
      s"RDD[labeldPoints] in PreparedData cannot be empty." +
      " Please check if DataSource generates TrainingData" +
      " and Preprator generates PreparedData correctly.")



    //var m=Map[Integer,Integer]()
    //var categoricalFeaturesInfo: java.util.Map[Integer,Integer] = mapAsJavaMap[Integer, Integer](m)
    //val impurity = "gini"
    
    //val stat= new Strategy(algo = Classification, impurity = Gini, ap.maxDepth, ap.numClasses,ap.maxBins, categoricalFeaturesInfo)
    //val tree=new DecisionTree(stat)
    //tree.run(data.labeledPoints)
    //Map("red" -> "#FF0000", "azure" -> "#F0FFFF")

    new LempelZivAlgorithmModel(
        user          = 1,
        userFeatures  = 7,
        userPredictio = -1
    )
    
  }

  def predict(model: LempelZivAlgorithmModel, query: Query): PredictedResult = {



   // val label = model.predict(Vectors.dense(query.features))
   // new PredictedResult(label)

    /*
    val gendersMap = model.gendersMap
    val educationMap = model.educationMap
    val randomForestModel = model.randomForestModel
    val label = randomForestModel.predict(
      Vectors.dense(Array(
        gendersMap(query.gender),
        query.age.toDouble,
        educationMap(query.education))
      ))
    * */

   val label = 69

   new PredictedResult(label)

  }

}
