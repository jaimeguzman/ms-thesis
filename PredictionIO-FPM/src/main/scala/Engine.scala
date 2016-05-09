package org.template.fpm

/*
 * Copyright KOLIBERO under one or more contributor license agreements.  
 * KOLIBERO licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import io.prediction.controller.{Engine,EngineFactory}
import org.joda.time.DateTime

case class Query(
  val items: Array[String]
) extends Serializable

case class PredictedResult(
  consequentItems: Array[ConsequentItem]
) extends Serializable {
  override def toString: String = consequentItems.mkString(",")
}

case class ConsequentItem(
  items: Array[String],
  confidence: Double
) extends Serializable

object FPMEngine extends EngineFactory {
  def apply() = {
    new Engine(
      classOf[DataSource],
      classOf[Preparator],
      Map("fpg" -> classOf[FPGAlgorithm]),
      	classOf[Serving])
  }
}
