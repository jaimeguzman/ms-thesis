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

case class AlgorithmParams(
  
  numClasses: Integer,
  maxDepth: Integer,
  maxBins: Integer
) extends Params

// extends P2LAlgorithm because the MLlib's NaiveBayesModel doesn't contain RDD.
class Algorithm(val ap: AlgorithmParams)
  extends P2LAlgorithm[PreparedData, DecisionTreeModel, Query, PredictedResult] {

  @transient lazy val logger = Logger[this.type]

  def train(sc: SparkContext,data: PreparedData): DecisionTreeModel = {
    // MLLib DecisionTree cannot handle empty training data.
    require(!data.labeledPoints.take(1).isEmpty,
      s"RDD[labeldPoints] in PreparedData cannot be empty." +
      " Please check if DataSource generates TrainingData" +
      " and Preprator generates PreparedData correctly.")
      
    var m=Map[Integer,Integer]()
    var categoricalFeaturesInfo: java.util.Map[Integer,Integer] = mapAsJavaMap[Integer, Integer](m)
    val impurity = "gini"
    
    val stat= new Strategy(algo = Classification, impurity = Gini, ap.maxDepth, ap.numClasses,ap.maxBins, categoricalFeaturesInfo)
    val tree=new DecisionTree(stat)
    tree.run(data.labeledPoints)
    
  }

  def predict(model: DecisionTreeModel, query: Query): PredictedResult = {
    val label = model.predict(Vectors.dense(query.features))
    new PredictedResult(label)

  }

}
