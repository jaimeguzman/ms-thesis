#!/bin/sh


echo $'\e[38;5;82m...This is PIO \e[38;5;198mCompressPredict Engine'
echo $'\e[34m''PLEASE WAIT...\e[39m'
echo '\n'
# echo $'\e[31mHello World\e[0m'
echo $'First Command Execute \e[33m PIO BUILD'
echo $'\e[31mBUILDING PROCESS.... please wait... \e[0m \e[39m'
echo '\n'

/Users/jguzman/PredictionIO/bin/pio build --clean
wait

echo '\n'
echo $'Second Command Execute \e[33m PIO TRAIN'
echo $'\e[31mTRAINING PROCESS.... please be patience.\e[39m'
echo '\n'

# /Users/jguzman/PredictionIO/bin/pio train -- --driver-memory 8G --executor-memory 8G --verbose
/Users/jguzman/PredictionIO/bin/pio train -- --driver-memory 8G --executor-memory 8G
wait

echo '\n'
echo $'Third Command Execute \e[33m PIO DEPLOY'
echo $'\e[31mREADY TO ROCK !.... please wait to start the server.\e[39m'
echo '\n\n'
# /Users/jguzman/PredictionIO/bin/pio deploy -- --driver-memory 2G --executor-memory 2G --verbose
/Users/jguzman/PredictionIO/bin/pio deploy -- --driver-memory 2G --executor-memory 2G