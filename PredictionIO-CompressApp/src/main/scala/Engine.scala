package cl.jguzman.piocompressapp

import io.prediction.controller.{Engine, EngineFactory}

class Query(
  val features: Array[Double]

) extends Serializable



class PredictedResult(
  val label: Double

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
