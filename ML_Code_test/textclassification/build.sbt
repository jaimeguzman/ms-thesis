
name := "org.template.textclassification"

organization := "io.prediction"

libraryDependencies ++= Seq(
  "io.prediction"    %% "core"        % pioVersion.value % "provided",
  "org.apache.spark" %% "spark-core" % "1.3.1" % "provided",
  "org.apache.spark" %% "spark-mllib" % "1.3.1" % "provided",
  "org.xerial.snappy" % "snappy-java" % "1.1.1.7"
)
