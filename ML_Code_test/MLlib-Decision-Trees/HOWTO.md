#Decision Tree Classification using MLlib

This Tutorial will describe how the Classification Template from PredictionIO (http://templates.prediction.io/PredictionIO/template-scala-parallel-classification) can be modified to use the Decision tree model of MLlib. 


## Algorithm.scala

Make sure you have imported the following:

```Scala
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

```

The AlgorithmParams class helps us get the parameters as arguements during runtime so that we need not have to re-compile the whole code again.
This is how our AlgorithmParams class looks like:
```Scala
case class AlgorithmParams(
  
  numClasses: Integer,
  maxDepth: Integer,
  maxBins: Integer
) extends Params
```
These parameters are set in the *engine.json* file in our main directory
```
{
  "id": "default",
  "description": "Default settings",
  "engineFactory": "org.template.classification.ClassificationEngine",
  "datasource": {
    "params": {
      "appId": 1
    }
  },
  "algorithms": [
    {
      "name": "decisiontree",
      "params": {
        
        "numClasses": 3,
        "maxDepth": 5,
        "maxBins": 100      
      }
    }
  ]
}
```
This is our Algorithm class:
```Scala
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
```
Notice the change we have made to train and predict functions. Also notice the small change to the definition of Algorithm class as below:
```Scala

class Algorithm(val ap: AlgorithmParams)
  extends P2LAlgorithm[PreparedData, DecisionTreeModel, Query, PredictedResult] {
```

The decision tree model needs a Statergy class object to initialize itself. The Strategy class needs to know the algorithm , the inpurity indx to use and other parameters as mentioned.
It also requires to know the set of categorical features in the dataset. It is given as input as a Map between the index of that feature and the number of categorical values it can take.
In our example we pass a empty Map as we are not using any categorical variables.

## DataSource.scala

If you are using the same sample data as that of the Classification Template, then you donot need to make many changes here.
Make sure the code is as following:
```Scala
import io.prediction.controller.PDataSource
import io.prediction.controller.EmptyEvaluationInfo
import io.prediction.controller.EmptyActualResult
import io.prediction.controller.Params
import io.prediction.data.storage.Event
import io.prediction.data.storage.Storage
import org.apache.spark.SparkContext
import org.apache.spark.SparkContext._
import org.apache.spark.rdd.RDD
import org.apache.spark.mllib.regression.LabeledPoint
import org.apache.spark.mllib.linalg.Vectors
import grizzled.slf4j.Logger

case class DataSourceParams(appId: Int) extends Params

class DataSource(val dsp: DataSourceParams)
  extends PDataSource[TrainingData,
      EmptyEvaluationInfo, Query, EmptyActualResult] {

  @transient lazy val logger = Logger[this.type]

  override
  def readTraining(sc: SparkContext): TrainingData = {
    val eventsDb = Storage.getPEvents()
    val labeledPoints: RDD[LabeledPoint] = eventsDb.aggregateProperties(
      appId = dsp.appId,
      entityType = "user",
      // only keep entities with these required properties defined
      required = Some(List("plan", "attr0", "attr1", "attr2")))(sc)
      // aggregateProperties() returns RDD pair of
      // entity ID and its aggregated properties
      .map { case (entityId, properties) =>
        try {
          LabeledPoint(properties.get[Double]("plan"),
            Vectors.dense(Array(
              properties.get[Double]("attr0"),
              properties.get[Double]("attr1"),
              properties.get[Double]("attr2")
            ))
          )
        } catch {
          case e: Exception => {
            logger.error(s"Failed to get properties ${properties} of" +
              s" ${entityId}. Exception: ${e}.")
            throw e
          }
        }
      }.cache()

    new TrainingData(labeledPoints)
  }
}

class TrainingData(
  val labeledPoints: RDD[LabeledPoint]
) extends Serializable

```

If you have some other dataset to test on, add those attributes in the list and add the corresponding *properties.get[Double]("<attr name>")*.
You need to import the events to the server in the same way ( with the same attribute names). For that change /data/import_eventserver.py accordingly.


