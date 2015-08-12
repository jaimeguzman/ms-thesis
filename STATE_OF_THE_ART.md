El resumen no debe contener menos de 100 palabras ni mas de 300 palabras.
=========




Las predicciones en las ciencias de la computación siempre ha sido constante desafio, tanto para tomar decisiones, dar recomendaciones, o ayudar a mejorar desarrollos. En la literura encontramos bastante interes por poder usar metodologías que permitan prediciones certeras.


=============================================================================

Del paper:
Dynamic and memory efficient web page prediction model using LZ78 and LZW algorithms

- Las predicciones basadas en Web access pattern ha atraido una imporante a atraccion.
- Este paper presentan un modelo de prediccion "online"

- Detecting the user interests and so recommending related pages or goods for e-commerce web sites [3], improving search engines results

- In most of the web usage mining techniques, sequences are either used to produce association rules or to produce tree structures or Markov chains to represent navigation patterns. Markov models are based on a well-established theory and are simple to understand.
 They wildly used for modeling user navigation path. 

In recent years the content of many web sites are dynamic and new pages are also added to site dynamically. So we need a model that can be online and consider the changes of web site and user behavior. 

The memory efficiency is an important factor for an online algorithm. Most of the current models proposed for prediction are not online [8, 9] and need an offline component for processing tasks and online models such as model that proposed in [7] may soon become too big to fit in memory.



Individual models require more space, and may be less accurate because they see less data than a global model [10].




Various models have been proposed for modeling the user navigation behavior and predicting the next requests of users. According to [12], association rules, sequential pattern discovery, clustering, and classification are most popular methods for web usage mining. 

Collaborative filtering is another method for modeling users' behaviors. 

Association rules [6] were proposed to capture the co- occurrences of buying different items in a supermarket shopping. Association rules indicate groups that are related together. Methods that use association rules can be found in [6, 7]. Collaborative filtering techniques are often


One of the famous predictors is all kth-order Prediction- by-Partial-Match, PPM predictor. All-kth-Order Markov
model maintains Markov predictors of order i, for all 1 <= i < k [2]

This model has improved prediction coverage and
accuracy but the number of states in the model grows exponentially when the order of model increases. Lower order Markov models are not very accurate in predicting the user’s browsing behavior, since these models do not look far into the past to correctly discriminate the different observed patterns.

Higher order Markov models give better prediction precision with reduced hit rate.

Improvements on the efficiency of PPM were examined in [6]. Three pruning criteria are proposed: a) support- pruning, b) confidence-pruning, c) error-pruning. The subject of [6] is mainly the efficiency. The resulting model, called Selective Markov Model has a low state complexity. But this model is not online and cannot be incrementally updated. The Longest Repeating Subsequence, LRS PPM [8] stores a subset of all passes that are frequently accessed. It uses longest repeated sequence to predict next request. In this model each path occurs more than some Threshold T, where T typically equals one.

LZ78 consume less memory than LZW, but has less hit rate and precision. In LZW last input is remained and so it can contain more sequences than LZ78. LZW has the best precision and hit rate and also needs less memory and computational power than other models. It seems that LZW algorithm is the best if we consider the precision, memory efficiency and running speed together.


==============================================================================
PAPER::::
A NEW MARKOV MODEL FOR WEB ACCESS PREDICTION
==============================================================================




Web user access behavior can minimize user-perceived latency, which is crucial in the rapidly growing World Wide Web.



However, if we could predict future user re- quests, we could put those pages into the client- side cache when the browser is free. 



Our hybrid-order tree-like Markov model can predict Web access precisely, providing high coverage and good scalability. HTMM intelli- gently merges two methods: a tree-like structure Markov model method that aggregates the ac- cess sequences by pattern matching and a hy- brid-order method that combines varying-order Markov models. Performance evaluations com- paring our HTMM with traditional Markov models confirm its usefulness.




==============================================================================
PAPER::::
On Prediction Using Variable Order Markov Models
==============================================================================





There is an intimate relation between prediction of discrete sequences and lossless com- pression algorithms, where, in principle, any lossless compression algorithm can be used for prediction and vice versa (see, e.g., Feder & Merhav, 1994)








3.1 Lempel-Ziv 78 (LZ78)
The lz78 algorithm is among the most popular lossless compression algorithms (Ziv & Lem- pel, 1978). It is used as the basis of the Unix compress utility and other popular archiving utilities for PCs. It also has performance guarantees within several analysis models. This algorithm (together with the lz77 compresion method) attracted enormous attention and inspired the area of lossless compression and sequence prediction.
The prediction component of this algorithm was first discussed by Langdon (1983) and Rissanen (1983). The presentation of this algorithm is simplified after the well-known lz78 compression algorithm, which works as follows, is understood. Given a sequence q1n ∈ Σn, lz78 incrementally parses q1n into non-overlapping adjacent ‘phrases’, which are collected into a phrase ‘dictionary’. The algorithm starts with a dictionary containing the empty phrase ǫ. At each step the algorithm parses a new phrase, which is the shortest phrase that is not yet in the dictionary.





Thus, the lz78 algorithm is a universal prediction algorithm with respect to the large class of stationary and ergodic Markov sources of finite order.