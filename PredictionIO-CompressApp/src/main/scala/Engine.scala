package cl.jguzman.piocompressapp

import io.prediction.controller.{Engine, EngineFactory}



class Query(q: String) extends Serializable{

  println( "Entro a QUERY ")

}


class PredictedResult(
  val label: Double

) extends Serializable{

  println( "Entro a PREDICT RESULT  ")

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
