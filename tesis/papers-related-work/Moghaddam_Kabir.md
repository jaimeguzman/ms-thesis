
# Frases 

Web access prediction has attracted significant attention in recent years. Web prefetching and some personalization systems use prediction algorithms

Navegacion -> o == Web access prediction -> prediction


# Basicamente lo que defiende
Most current applications that predict the next user web page have an offline component that does the data preparation task and an online section that provides personalized content to the users based on their current navigational activities.


# Su propuesta 
 Our algorithm is based on LZ78 and LZW algorithms that are adapted for modeling the user navigation in web. Our model decreases computational complexities which is a serious problem in developing online prediction systems. A performance evaluation is presented using real web logs. This evaluation shows that our model needs much less memory than PPM family of algorithms with good prediction accuracy.

 In this paper we present efficient techniques for modeling user navigation behavior. Our model is online so changes in user request patterns will update our prediction model incrementally. We do not build per-user predictive models. 



# Contexto

In recent years the content of many web sites are dynamic and new pages are also added to site dynamically. So we need a model that can be online and consider the changes of web site and user behavior. The memory efficiency is an important factor for an online algorithm. Most of the current models proposed for prediction are not online [8, 9] and need an offline component for processing tasks and online models such as model that proposed in [7] may soon become too big to fit in memory.



# Autores que relacionan su trabajo

Most of the current models proposed for prediction are not online [8, 9]

>J. Pitkow and P. Pirolli, "Mining longest repeating subsequences to predict world wide web surfing," USENIX Association Berkeley, CA, USA, 1999, pp. 13-13.
[9] X. Chen and X. Zhang, "A Popularity-Based Prediction Model for Web Prefetching," IEEE Computer Society, 2003.



According to [12], association rules, sequential pattern discovery, clustering, and classification are most popular methods for web usage mining. Collaborative filtering is another method for modeling users' behaviors. Association rules [6] were proposed to capture the co- occurrences of buying different items in a supermarket shopping. Association rules indicate groups that are related together.


# Primera aproximacion a cruce con Markov

There is an arc from node A to B if and only if at some point in time a client accessed to B within w accesses after A, where w is the lookahead window size. The weight of the arc is the ratio of the number of accesses to B within a window after A to the number of accesses to A itself. A DG is effectively a first-order Markov model. In this method the consecution of requests is not considered. A first-order Markov model for a collection of user navigation sessions is proposed in [13], this method is extended in [14] to represent higher order conditional probabilities by making use of a cloning operation.




> [13] J. Borges and M. Levene, "Data Mining of User Navigation Patterns," Springer-Verlag London, UK, 1999, pp. 92-111.
[14] J. Borges and M. Levene, "Generating dynamic higher-order Markov models in web usage mining." vol. 3721: Springer, 2005, pp. 34-45.



# Despues hace un acercamiento a PPM con Markov










# Sobre las tecnicas que aborda

Large number of states in markov models, pattern in sequential pattern and association rules led to need much runtime requirements such as memory and computation power.



# Linda forma de citar a LZ

In this section we propose two algorithms that are based on LZ78 and LZW. LZ78 algorithm is proposed by Jacob Ziv and Abraham Lempel in 1977 [15]. 



# LZ78

LZ78 basically are lossless data compression algorithms with good functionality. The most important part of these algorithms is the dictionary construction algorithm that we use it for creating the prediction model.




