package org.template.classification
import scala.collection.JavaConverters._
import scala.collection.JavaConversions._

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
  lambda: Double
) extends Params

// extends P2LAlgorithm because the MLlib's NaiveBayesModel doesn't contain RDD.
class Algorithm(val ap: AlgorithmParams)
  extends P2LAlgorithm[PreparedData, DecisionTreeModel, Query, PredictedResult] {

  @transient lazy val logger = Logger[this.type]

  def train(data: PreparedData): DecisionTreeModel = {
    // MLLib DecisionTree cannot handle empty training data.
    require(!data.labeledPoints.take(1).isEmpty,
      s"RDD[labeldPoints] in PreparedData cannot be empty." +
      " Please check if DataSource generates TrainingData" +
      " and Preprator generates PreparedData correctly.")
      
    val numClasses = 3
    var m=Map[Integer,Integer]()
    var categoricalFeaturesInfo: java.util.Map[Integer,Integer] = mapAsJavaMap[Integer, Integer](m)
    val impurity = "gini"
    val maxDepth = 5
    val maxBins = 100
    //val algo=new Algo.Algo()
    //Impurity impurity=Gini.instance()
    //Algo.Algo al=Algo.Classification()
    //val stat= new Strategy(Algo.Classification,Gini.instance, maxDepth, numClasses,maxBins, categoricalFeaturesInfo)
    val stat= new Strategy(algo = Classification, impurity = Gini, maxDepth, numClasses,maxBins, categoricalFeaturesInfo)
    
    val tree=new DecisionTree(stat)
    tree.run(data.labeledPoints)
    //DecisionTree.trainClassifier(trainingData, numClasses, categoricalFeaturesInfo,  impurity, maxDepth, maxBins)
    //NaiveBayes.train(data.labeledPoints, ap.lambda)
  }

  def predict(model: DecisionTreeModel, query: Query): PredictedResult = {
    val label = model.predict(Vectors.dense(query.features))
    new PredictedResult(label)

  }

}
