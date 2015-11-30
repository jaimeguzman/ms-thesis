package cl.jguzman.piocompressapp

import grizzled.slf4j.Logger


//CONTROLLLER
import io.prediction.controller.PDataSource
import io.prediction.controller.EmptyEvaluationInfo
import io.prediction.controller.EmptyActualResult
import io.prediction.controller.Params

//STORAGE
import io.prediction.data.storage.Storage
import io.prediction.data.storage.Event

//SPARK
import org.apache.spark.SparkContext
import org.apache.spark.rdd.RDD




/*
* Parametros para la lectura de datos de origen.
*
* */
case class DataSourceParams(
    appId: Int

) extends Params







class DataSource(val dsp: DataSourceParams)
  extends PDataSource[TrainingData,
                    EmptyEvaluationInfo,
                    Query,
                    EmptyActualResult] {

  @transient lazy val logger = Logger[this.type]

  override def readTraining(sc: SparkContext): TrainingData = {

    println("\n::::::::RATSLABS:::Recuperando Información desde el servidor de eventos.")
    val eventosDB = Storage.getPEvents()


    val eventosRDD : RDD[Event] =  eventosDB.find(
                            appId = dsp.appId,
                            entityType = Some("user")
                          )(sc)

    val webAccessRDD:RDD[WebAccess] = eventosRDD.map {ev =>
                  val userAccess = ev.event match {
                      case "view" =>
                        WebAccess(Some(ev.entityId.toInt),
                                  Some(ev.properties.get[String]("page")),
                                  Some(ev.properties.get[Int]("pos")))

                      case _ => throw new Exception(s"Evento no esperado, ${ev} ha sido leido")

                    }

        userAccess
    }.cache()

    //println("::::::::RATSLABS:::webAcessRDD "+webAccessRDD.getClass )
    //webAccessRDD.foreach( f => println( f ) )
   // println("\n::::::::RATSLABS::: labeledPOINTS loaded count()"+ webAccessRDD.count())


    new TrainingData(webAccessRDD)
  }
}

case class WebAccess( user: Option[Int],page: Option[String],pos:  Option[Int])
  extends Serializable with Ordered[WebAccess] {


  val orderingById: Ordering[WebAccess] = Ordering.by(e => e.user.get )

  import scala.math.Ordered.orderingToOrdered
  def compare( a:WebAccess ) = user.get.compareTo(a.user.get)

  //def compare(that: WebAccess): Int = (this.user.get, this.load) compare (that.tag, that.load)

}


class TrainingData(
     val webaccess: RDD[WebAccess]
) extends Serializable
