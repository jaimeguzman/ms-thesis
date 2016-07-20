> Big Data Analytics with Spark: A Practitioner’s Guide to Using Spark for Large-Scale Data Processing, Machine Learning, and Graph Analytics, and High-Velocity Data Stream Processing


Interest in machine learning is growing by leaps and bounds. It has gained a lot of momentum in recent years for a few reasons. The first reason is performance improvements in hardware and algorithms. Machine learning is compute-intensive. With proliferation of multi-CPU and multi-core machines and efficient algorithms, it has become feasible to do machine learning computations in reasonable time. The second reason is that machine learning software has become freely available. Many good quality open source machine learning software are available now for anyone to download. The third reason is that MOOCs (massive open online courses) have created tremendous awareness about machine learning. These courses have democratized the knowledge required to use machine learning. Machine learning skills are no longer limited to a few people with Ph.D. in Statistics. Anyone can now learn and apply machine learning techniques.

Machine learning is embedded in many applications that we use on a daily basis. Apple, Google, Facebook, Twitter, LinkedIn, Amazon, Microsoft, and numerous others use machine learning under the hood in many of their products. Examples of machine learning applications include driverless car, motion-sensing game consoles, medical diagnosis, email spam filtering, image recognition, voice recognition, fraud detection, and movie, song, and book recommendations.

This chapter introduces core machine learning concepts and then discusses the machine learning libraries that Spark provides. Machine learning is a broad topic; it can be the subject of a book by itself. In fact, several books have been written on it. Covering it in detail is out of scope for this book; the next section introduces the basic concepts, so that you can follow the rest of the material in this chapter. If you are familiar with machine learning, you can skip the next section.



Introducing Machine Learning

Machine learning is the science of training a system to learn from data and act. The logic that drives the behavior of a machine learning-based system is not explicitly programmed but learnt from data.

A simple analogy is an infant learning to speak by observing others. Babies are not born with any language skills, but they learn to understand and speak words by observing others. Similarly, in machine learning, we train a system with data instead of explicitly programming its behavior.

To be specific, a machine learning algorithm infers patterns and relationships between different variables in a dataset. It then uses that knowledge to generalize beyond the training dataset. In other words, a machine learning algorithm learns to predict from data.

Let’s introduce some of the terms generally used in the context of machine learning.





# Models

A model is a mathematical construct for capturing patterns within a dataset. It estimates the relationship between the dependent and independent variables in a dataset. It has predictive capability. Given the values of the independent variables, it can calculate or predict the value for the dependent variable. For example, consider an application that forecasts quarterly sales for a company. The independent variables are number of sales people, historical sales, macro-economic conditions, and other factors. Using machine learning, a model can be trained to predict quarterly sales for any given combination of these factors.

A model is basically a mathematical function that takes features as input and outputs a value. It can be represented in software in numerous ways. For example, it can be represented by an instance of a class. We will see a few concrete examples later in this chapter.

A model along with a machine learning algorithm forms the heart of a machine learning system. A machine learning algorithm trains a model with data; it fits a model over a dataset, so that the model can predict the label for a new observation.

Training a model is a compute intensive task, while using it is not as compute intensive. A model is generally saved to disk, so that it can be used in future without having to go through the compute intensive training step again. A serialized model can also be shared with other applications. For example, a machine learning system may consist of two applications, one that trains a model and another that uses a model




Decision Trees

The Decision Tree algorithm was covered under the section covering regression algorithms. As mentioned earlier, Decision Trees can be used for both regression and classification tasks. The algorithm works the same way in both cases except for one thing - the values stored at the terminal (leaf) nodes.

For regression tasks, each terminal node stores a numeric value; whereas for classification tasks, each terminal node stores a class label. Multiple leaves may have the same class label. To predict a label for an observation, a decision tree model starts at the root node of a decision tree and tests the features against the internal nodes until it arrives at a leaf node. The value at the leaf node is the predicted label.