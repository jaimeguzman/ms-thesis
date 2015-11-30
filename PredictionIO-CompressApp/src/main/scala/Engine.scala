package cl.jguzman.piocompressapp

import io.prediction.controller.{Engine, EngineFactory}



case class Query(
                  webaccess: String,
                  num: Int

             ) extends Serializable



class PredictedResult(
  val result: String

) extends Serializable{
//  println( "Entro a PREDICT RESULT  ")
}



//https://docs.prediction.io/api/current/index.html#io.prediction.controller.EngineFactory
object LempelZivEngine extends EngineFactory {


  def apply() = {
    new Engine(
      classOf[DataSource],
      classOf[Preparator],
      Map("lempelziv" -> classOf[Algorithm]),
      classOf[Serving])
  }


}
