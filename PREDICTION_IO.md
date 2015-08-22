


Para comenzar PIO, es un framework mas orientado a web y servir resultados,
por lo cual se puede poner en producción y dar varias casos de aplicación:


## Para usarlo es requerido primero crear un app

[INFO] [HBLEvents] The table pio_event:events_2 doesn't exist yet. Creating now...
[INFO] [App$] Initialized Event Store for this app ID: 2.
[INFO] [App$] Created new app:
[INFO] [App$]       Name: textclassification
[INFO] [App$]         ID: 2
[INFO] [App$] Access Key: NIX41EICsuQTnRYQ0uTvO7EPxAUis496ze5BSfKqeR73DJfVl66NYM6DLpNuTowP


## Luego se debe meter la data 


 pio import --appid 2 --input data/stopwords.json &&  pio import --appid 2 --input data/emails.json


## Despues de entregarle data se debe crear el engine con el comando pio build

```Tener consideración los recursos de memoria de donde se hacen las pruebas```

*El resultado de un entrenamiento y creación del engine que posea internamente el modelo, es:*


[INFO] [Console$] Using command '/home/vagrant/PredictionIO/sbt/sbt' at the current working directory to build.
[INFO] [Console$] If the path above is incorrect, this process will fail.
[INFO] [Console$] Uber JAR disabled. Making sure lib/pio-assembly-0.9.4.jar is absent.
[INFO] [Console$] Going to run: /home/vagrant/PredictionIO/sbt/sbt  package assemblyPackageDependency
[INFO] [Console$] Build finished successfully.
[INFO] [Console$] Looking for an engine...
[INFO] [Console$] Found org-template-textclassification_2.10-0.1-SNAPSHOT.jar
[INFO] [Console$] Found org.template.textclassification-assembly-0.1-SNAPSHOT-deps.jar
[INFO] [RegisterEngine$] Registering engine WwoQ2ERKCZSyAQkQ4P48er2kb3a1eMfH 9cf05f5cd78811382782f51a18d3d4757ed4d9f5
[INFO] [Console$] Your engine is ready for training.



# Despues debe hacer el entrenamiento:




# Despues servir los datos con deploy
```

pio deploy -- --driver-memory 8G --executor-memory 4G

-- --driver-memory 2G --executor-memory 2G --conf spark.akka.framesize=2 --total_executor_cores 4

```

# Por ultimo para conusmir y/o usar los datos sería un curl al servidor PIO.


curl -H "Content-Type: application/json" -d '{ "text":"I like speed and fast motorcycles." }' http://192.168.67.67/:8000/queries.json


#Algunas capturas 


https://dl.dropboxusercontent.com/spa/srrxi5k8b49mdt9/70lvfxm-.png

https://dl.dropboxusercontent.com/spa/srrxi5k8b49mdt9/-u_h9sod.png


https://dl.dropboxusercontent.com/spa/srrxi5k8b49mdt9/rebsd4xb.png

https://dl.dropboxusercontent.com/spa/srrxi5k8b49mdt9/9b5mk918.png

> El Server PIO corriendo, pero usandolo como un clasificador de texto:

https://dl.dropboxusercontent.com/spa/srrxi5k8b49mdt9/ca88tc_v.png


# Cosas de SCala
https://hub.docker.com/r/williamyeh/scala/
https://github.com/zdlopez


# El history de la consola, usado en MBP
```
   57  cd test-textclassification/
   58  ll
   59  pio app new MyTextApp
   60  pio import --appid 1 --input data/stopwords.json
   61  pio import --appid 1 --input data/emails.json
   62  pio build
   63  exit
   64  pio eventserver --ip 0.0.0.0
   65  exit
   66  cd /
   67  ll
   68  cd vagrant/
   69  ll
   70  cd templates/
   71  ll
   72  pwd
   73  cd test-textclassification/
   74  ll
   75  pio app list
   76  time pio build
   77  exit
   78  pio eventserver --ip 0.0.0.0
   79  exit
   80  pio-stop-all 
   81  exit
   82  cd /vagrant/
   83  ll
   84  cd templates/
   85  ll
   86  pio app list
   87  pwd
   88  ll
   89  cd test-textclassification/
   90  ll
   91  time pio build
   92  time pio train
   93  pwd
   94  ll
   95  time pio train
   96  pio-start-all
   97  pio train
   98  pio status
   99  pwd
  100  ll
  101  pio build --clean
  102  exit
  103  ll
  104  cd /vagrant/
  105  ll
  106  cd templates/
  107  ll
  108  pwd
  109  ll
  110  cd test-textclassification/
  111  ll
  112  pio app list
  113  vim engine.json 
  114  ll
  115  pwd
  116  ll
  117  time pio build clean
  118  pwd
  119  ll
  120  time pio build --clean
  121  time pio train
  122  ll
  123  cd ..
  124  ll
  125  rm -fr test-textclassification/
  126  pio template get PredictionIO/template-scala-parallel-textclassification textclassification
  127  ll
  128  cd textclassification/
  129  ll
  130  pio app new textclassification
  131  pio import --appid 2 --input data/stopwords.json &&  pio import --appid 2 --input data/emails.json
  132  ll
  133  pio build
  134  pio train --verbose
  135  pio deploy --verbose
  136  pio deploy --debug
  137  pio deploy 
  138  pio deploy -- --driver-memory 8G
  139  pio deploy --driver-memory 4G --executor-memory 4G
  140  pio deploy -- --driver-memory 8G --executor-memory 4G
  141  pwd
  142  ll
  143  less hs_err_pid8253.log 
  144  pio deploy -- --driver-memory 2G --executor-memory 2G --conf spark.akka.framesize=2 --total_executor_cores 4
  145  pio deploy -- --driver-memory 2G --executor-memory 2G --conf spark.akka.framesize=2 
  146  history

```


