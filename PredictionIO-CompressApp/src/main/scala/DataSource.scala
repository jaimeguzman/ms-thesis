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
import scala.collection.mutable.Stack

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
                    ActualResult] {

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




    new TrainingData(webAccessRDD)
  }

  override def readEval(sc: SparkContext): Seq[(TrainingData,
                                                EmptyEvaluationInfo,
                                                RDD[(Query,
                                                ActualResult)])] = {


    // The following code reads the data from data store. It is equivalent to
    // the readTraining method. We copy-and-paste the exact code here for
    // illustration purpose, a recommended approach is to factor out this logic
    // into a helper function and have both readTraining and readEval call the
    // helper.
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
    // End of reading from data store


    println("\t\t::::::::::readEval::::::::::::\t\t" )


    /**
    // K-fold splitting
    val evalK = dsp.evalK.get
    val indexedPoints: RDD[(LabeledPoint, Long)] = labeledPoints.zipWithIndex()

    (0 until evalK).map { idx =>
      val trainingPoints = indexedPoints.filter(_._2 % evalK != idx).map(_._1)
      val testingPoints = indexedPoints.filter(_._2 % evalK == idx).map(_._1)

      (
        new TrainingData(trainingPoints),
        new EmptyEvaluationInfo(),
        testingPoints.map {
          p => (new Query(p.features(0), p.features(1), p.features(2)), new ActualResult(p.label))
        }
        )
    }
    */



    /**Folds Limits**/
    val foldTraining: Int =  90
    val foldTesting:  Int = foldTraining

    /**Training**/
    val trainingSequences     = webAccessRDD.filter( _.user.get < foldTraining    )

    /**Testing**/
    val testingSequences      = webAccessRDD.filter( _.user.get >= foldTesting )
                                                    .map( u=> (u.user, u.page ))

    val testingSequencesGroup = webAccessRDD.groupBy(_.user)


    (0 until  foldTesting  ).map {
      idx =>
        var tmp:String = ""
        ( new TrainingData(trainingSequences),
          new EmptyEvaluationInfo,
          testingSequencesGroup.filter(_._1.get > foldTesting ).map {

            p =>

              var penultima:String=""
              var ultima:String=""

              for( i <- p._2) tmp +=  i.page.get ;
              if( tmp.length >1 ){
                penultima = tmp.charAt(tmp.length-2 ).toString
                ultima    = tmp.charAt(tmp.length-1 ).toString
              }
              println(  "DATASOURCE >>> penultimate page= "+ penultima + "  last page= "+ ultima+"  session= "+tmp)
              
              tmp = ""


              ( new Query( penultima  , 1), new ActualResult( ultima ) )



          }
        )
    }




  }
}







case class WebAccess( user: Option[Int],page: Option[String],pos:  Option[Int])
  extends Serializable with Ordered[WebAccess] {


  val orderingById: Ordering[WebAccess] = Ordering.by(e => e.user.get )


  def compare( a:WebAccess ) = user.get.compareTo(a.user.get)



}


class TrainingData(
     val webaccess: RDD[WebAccess]
) extends Serializable
