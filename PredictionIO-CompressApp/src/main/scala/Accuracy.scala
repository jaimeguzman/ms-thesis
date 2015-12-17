package cl.jguzman.piocompressapp

import io.prediction.controller.AverageMetric
import io.prediction.controller.EmptyEvaluationInfo
import io.prediction.controller.EngineParams
import io.prediction.controller.EngineParamsGenerator
import io.prediction.controller.Evaluation

case class Accuracy() extends
          AverageMetric[EmptyEvaluationInfo,
                        Query,
                        PredictedResult,
                        ActualResult] {


  println( "\t\t\t>>>>Acurracy check \t")

 var value  = 0.0
 var value2  = 0.0
 var error  = 0.0
 var counter = 0.0


  def calculate(query: Query,  predicted: PredictedResult, actual: ActualResult): Double = {


    counter+=1.0


     if(  predicted.result == actual.actualRes ){
       value2 +=1.0;
     }else{
       error +=1
     }
    // print("\ncalculate >>> "+"\tpagina predecida= "+predicted.result+ "\t pagina correcta= "  +actual.actualRes )
    // print("\tAccurracy = "+ ((value2/counter)*100).round + " % " )
    // print("\tValue= "+value2.round )
    // print("\tError= "+ error.round )
    // print("\t# pruebas= "+counter.round)


    if(  predicted.result == actual.actualRes ) 1.0 else 0.0

  }



}

object AccuracyEvaluation extends Evaluation {
  // Define Engine and Metric used in Evaluation
  engineMetric = ( LempelZivEngine(), new Accuracy() )
}

object EngineParamsList extends EngineParamsGenerator {
  // Define list of EngineParams used in Evaluation

  // First, we define the base engine params. It specifies the appId from which
  // the data is read, and a evalK parameter is used to define the
  // cross-validation.
  val baseEP = EngineParams( dataSourceParams = DataSourceParams( appId = 6 ))


   //println( baseEP.dataSourceParams._1 )
   //println( baseEP.dataSourceParams._2.toString )


  // Second, we specify the engine params list by explicitly listing all
  // algorithm parameters. In this case, we evaluate 3 engine params, each with
  // a different algorithm params value.
  //("naive", AlgorithmParams(10.0))
  engineParamsList = Seq(
    baseEP.copy(algorithmParamsList = Seq(("lempelziv", AlgorithmParams(5) ) )  ) )

 // engineParamsList(Seq())
}


