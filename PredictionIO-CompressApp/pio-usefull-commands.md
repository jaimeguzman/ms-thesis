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


# Deploy options:
$ pio deploy -- --driver-memory 2G --executor-memory 2G --conf spark.akka.framesize=2

```