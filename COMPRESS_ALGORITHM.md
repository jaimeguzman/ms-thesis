https://intranet.tuhh.de/kvvz/vorlesung.php?Lang=en&sg_s=ETMS&mid=551&xtype=s
Content:
Structure of a pattern recognition system, statistical decision theory, classification based on statistical models, polynomial regression, dimension reduction, multilayer perceptron regression, radial basis functions, support vector machines, unsupervised learning and clustering, algorithm-independent machine learning, mixture models and EM, adaptive basis function models and boosting, Markov random fields
Information, entropy, redundancy, mutual information, Markov processes, basic coding schemes (code length, run length coding, prefix-free codes), entropy coding (Huffman, arithmetic coding), dictionary coding (LZ77/Deflate/LZMA2, LZ78/LZW), prediction, DPCM, CALIC, quantization (scalar and vector quantization), transform coding, prediction, decorrelation (DPCM, DCT, hybrid DCT, JPEG, JPEG-LS), motion estimation, subband coding, wavelets, HEVC (H.265,MPEG-H)
Literature:
Schürmann: Pattern Classification, Wiley 1996
Murphy, Machine Learning, MIT Press, 2012
Barber, Bayesian Reasoning and Machine Learning, Cambridge, 2012
Duda, Hart, Stork: Pattern Classification, Wiley, 2001
Bishop: Pattern Recognition and Machine Learning, Springer 2006
Salomon, Data Compression, the Complete Reference, Springer, 2000
Sayood, Introduction to Data Compression, Morgan Kaufmann, 2006
Ohm, Multimedia Communication Technology, Springer, 2004
Solari, Digital video and audio compression, McGraw-Hill, 1997
Tekalp, Digital Video Processing, Prentice Hall, 1995



Comparison to Lempel-Ziv 78
Both LZ77 and LZ78 and their variants keep a
“dictionary” of recent strings that have been seen.
The differences are:
– How the dictionary is stored (LZ78 is a trie)
– How it is extended (LZ78 only extends an existing
entry by one character)
– How it is indexed (LZ78 indexes the nodes of the
trie)
– How elements are removed


https://docs.prediction.io/api/current/#io.prediction.controller.LAlgorithm