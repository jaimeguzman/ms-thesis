package org.template.classification

import grizzled.slf4j.Logger
import io.prediction.controller.{EmptyActualResult, EmptyEvaluationInfo, PDataSource, Params}
import io.prediction.data.storage.Storage
import org.apache.spark.SparkContext
import org.apache.spark.mllib.linalg.Vectors
import org.apache.spark.mllib.regression.LabeledPoint
import org.apache.spark.rdd.RDD


case class DataSourceParams(appId: Int) extends Params

class DataSource(val dsp: DataSourceParams)
  extends PDataSource[TrainingData,EmptyEvaluationInfo, Query, EmptyActualResult] {

  @transient lazy val logger = Logger[this.type]

  override
  def readTraining( sc: SparkContext): TrainingData = {

    val variableExample = ":::::::::...THIS IS A TEST....."

    println("::::::::::::: HOLA FUCKING MUNDO ...")

    println( variableExample )

    logger.info( ":::::: Aqui se empieza algo con event DB ::::" )

    val eventsDb = Storage.getPEvents()
    
    logger.info( ":::::::::" + s"${eventsDb}" )
    logger.info( "::::::  / event DB ::::" )




    println(" Antes de entrar a val labelPoints")
    val labeledPoints: RDD[LabeledPoint] = eventsDb.aggregateProperties(
      appId         = dsp.appId,
      entityType    = "user",
      // only keep entities with these required properties defined
      required      = Some(List("plan", "page", "pos")))(sc) // aggregateProperties() returns RDD pair of entity ID and its aggregated properties
      .map { case (entityId, properties) =>

        try {
          //logger.info( ":::::::::::::::::" +s"--- properties --"  )
          //logger.info( ":::::::::::::::::" +s"--- entityTYPE --" + s"${entityId} "  )
          //logger.debug( s"--- entityTYPE --" + s"${properties} "  )


          LabeledPoint(properties.get[Double]("plan"),
            Vectors.dense(Array(
              properties.get[Double]("page"),
              properties.get[Double]("pos")
            ))
          )
        } catch {
          case e: Exception => {
            logger.error(s"Failed to get properties ${properties} of" +  s" ${entityId}. Exception: ${e}.")
            throw e
          }
        }
      }.cache()



      logger.info(":::::::::Aqui  podria empezar a debuggear algo... de labeledPoints")
      logger.info(":::::::::" + s"${labeledPoints}" )
      logger.info(":::::::::" + s"  labeledPoints ")

      println( labeledPoints  )


    new TrainingData(labeledPoints)
  }
}

class TrainingData(
  val labeledPoints: RDD[LabeledPoint]
) extends Serializable
