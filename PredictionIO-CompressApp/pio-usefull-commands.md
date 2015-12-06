### Usefull PIO commands
```sh

# Start event server 
$ pio eventserver

# Import bash tool
$ pio import --appid XXX --input data/wazzaa.json


# fresh build
$ pio buil clean


# timing the build of your engine
$ time pio build


# Train options with timming:
$ time pio train -- --driver-memory 8G --executor-memory 4G --verbose
time pio train -- --driver-memory 8G --executor-memory 8G --verbose

# Deploy options:
pio deploy -- --driver-memory 2G --executor-memory 2G --conf spark.akka.framesize=2

#For debug options

pio deploy -- --driver-memory 2G --executor-memory 2G --verbose

http://localhost:7070/events.json?accessKey=nHpUz1bTdXY9b9Mi3VNWZYfTz5lA1G9hka8uGXaJHGMF1c15vUWkSePfONONhxDD



 pio eval cl.jguzman.piocompressapp.AccuracyEvaluation cl.jguzman.piocompressapp.EngineParamsList -- --driver-memory 1g

```