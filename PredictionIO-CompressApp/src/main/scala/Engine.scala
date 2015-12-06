package cl.jguzman.piocompressapp

import io.prediction.controller.{Engine, EngineFactory}


//This is the query for python cli
case class Query(webaccess: String,
                  num: Int
             ) extends Serializable


// this is the result  from predict funciton on Algortithm class
class PredictedResult(
  val result: String
) extends Serializable


class ActualResult(
  val actualRes: String
) extends Serializable


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
