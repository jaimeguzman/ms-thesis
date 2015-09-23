package org.template.vanilla

import io.prediction.controller.IEngineFactory
import io.prediction.controller.Engine

case class Query(q: String) extends Serializable

case class PredictedResult(p: String) extends Serializable

object VanillaEngine extends IEngineFactory {
  def apply() = {
    new Engine(
      classOf[DataSource],
      classOf[Preparator],
      Map("algo" -> classOf[Algorithm]),
      classOf[Serving])
  }
}
