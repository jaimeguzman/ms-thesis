#!/bin/sh


echo $'\e[38;5;82m...This is PIO \e[38;5;198mCompressPredict Engine Evaluator'
echo $'\e[34m''PLEASE WAIT...\e[39m'
echo '\n'
# echo $'\e[31mHello World\e[0m'
echo $'First Command Execute \e[33m PIO BUILD'
echo $'\e[31mBUILDING PROCESS.... please wait... \e[0m \e[39m'
echo '\n'

/Users/jguzman/PredictionIO/bin/pio build 
wait

echo '\n'
echo $'Second Command Execute \e[33m PIO EVAL'
echo $'\e[31m EVALUATION PROCESS.... please be patience.\e[39m'
echo '\n'

# /Users/jguzman/PredictionIO/bin/pio train -- --driver-memory 8G --executor-memory 8G --verbose
# /Users/jguzman/PredictionIO/bin/pio train -- --driver-memory 8G --executor-memory 8G
/Users/jguzman/PredictionIO/bin/pio  eval cl.jguzman.piocompressapp.AccuracyEvaluation cl.jguzman.piocompressapp.EngineParamsList -- --driver-memory 8G --executor-memory 8G 
# --verbose

wait

