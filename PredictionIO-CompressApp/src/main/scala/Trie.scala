package cl.jguzman.piocompressapp



import scala.annotation.tailrec
import scala.collection.JavaConverters._
import scala.collection.mutable
import scala.collection.mutable.ListBuffer
import scala.collection.mutable.Stack
import scala.util.Random


object Trie {
  def apply() : Trie = new TrieNode()
}

sealed trait Trie extends Traversable[String] {

  def append(key : String)
  def findByPrefix(prefix: String): scala.collection.Seq[String]
  def contains(word: String): Boolean
  def remove(word : String) : Boolean

};

class TrieNode(val char: Option[Char] = None,
               var word: Option[String] = None,
               var counter:Int= 0) extends Trie with Serializable{

  var trieHeigth = 0
  val children: mutable.Map[Char, TrieNode] = new java.util.TreeMap[Char, TrieNode]().asScala

  override def  append(key: String) = {


    @tailrec def appendHelper(node: TrieNode, currentIndex: Int): Unit = {

      if (currentIndex == key.length) {
        //System.out.println( "IF "+currentIndex+" == "+key.length+" - "+node.word+"\t "+node.counter )
        node.counter  += 1
        node.word     = Some(key)
      }else{

        val char      = key.charAt(currentIndex).toLower
        val result    = node.children.getOrElseUpdate(char, { new TrieNode(Some(char)) })

        node.counter  += 1

        //node.counter  += 1
        //System.out.println("char "+char+"\t"+result+"\t "+node.counter )
        //System.out.println( "EL "+currentIndex+" == "+key.length+" - "+node.word+"\t "+node.counter )
        appendHelper(result, currentIndex + 1)
      }


    }
    appendHelper(this, 0)
  }

  override def  foreach[U](f: String => U): Unit = {

    @tailrec def foreachHelper(nodes: TrieNode*): Unit = {
      if (nodes.size != 0) {
        nodes.foreach(node => node.word.foreach(f))
        foreachHelper(nodes.flatMap(node => node.children.values): _*)
      }
    }

    foreachHelper(this)
  }

  override def  findByPrefix(prefix: String): scala.collection.Seq[String] = {

    @tailrec def helper(currentIndex: Int,
                        node: TrieNode,
                        items: ListBuffer[String]): ListBuffer[String] = {
      if (currentIndex == prefix.length) {
        items ++ node
      } else {
        node.children.get(prefix.charAt(currentIndex).toLower) match {
          case Some(child) => helper(currentIndex + 1, child, items)
          case None => items
        }
      }
    }

    helper(0, this, new ListBuffer[String]())
  }

  override def  contains(word: String): Boolean = {

    @tailrec def helper(currentIndex: Int, node: TrieNode): Boolean = {
      if (currentIndex == word.length) {
        node.word.isDefined
      } else {
        node.children.get(word.charAt(currentIndex).toLower) match {
          case Some(child) => helper(currentIndex + 1, child)
          case None => false
        }
      }
    }

    helper(0, this)
  }

  override def  remove(word : String) : Boolean = {

    pathTo(word) match {
      case Some(path) => {
        var index = path.length - 1
        var continue = true

        path(index).word = None

        while ( index > 0 && continue ) {
          val current = path(index)

          if (current.word.isDefined) {
            continue = false
          } else {
            val parent = path(index - 1)

            if (current.children.isEmpty) {
              parent.children.remove(word.charAt(index - 1).toLower)
            }

            index -= 1
          }
        }

        true
      }
      case None => false
    }

  }


  def pathTo( word : String ) : Option[ListBuffer[TrieNode]] = {

    def helper(buffer : ListBuffer[TrieNode], currentIndex : Int, node : TrieNode) : Option[ListBuffer[TrieNode]] = {
      if ( currentIndex == word.length) {
        node.word.map( word => buffer += node )
      } else {
        node.children.get(word.charAt(currentIndex).toLower) match {
          case Some(found) => {
            buffer += node
            helper(buffer, currentIndex + 1, found)
          }
          case None => None
        }
      }
    }

    helper(new ListBuffer[TrieNode](), 0, this)
  }

  override def  toString() : String = s"Trie(char=${char},   \tpage= ${word},\tcounter= ${counter}}) chidls= ${this.children.size}} "

  def printTree[U](f: String => U): Unit = {
    println("epsilon");
    @tailrec def foreachHelper(nodes: TrieNode*): Unit = {
      if (nodes.size != 0) {
        //println("\tSZ"+nodes.size )
        println()
        println("--|")

        nodes.foreach(
          node =>{
            for(i <- 0 to node.children.size ){print("    ")}
          print(" "+node.children.size+"_[" )
          node.word.foreach(f)
          print("]#"+node.counter )
        }  )
        foreachHelper(nodes.flatMap(node => node.children.values): _*)

      }
    }

    foreachHelper(this)
  }


  def updateCounters[U](f: String => U): Unit = {
    @tailrec def foreachHelper(nodes: TrieNode*): Unit = {
      if (nodes.size != 0) {
        //println("\tSZ"+nodes.size )
        println()


        nodes.foreach(
          node =>{

            val aux = node.word
            if( aux!=None ) {
              node.children.foreach {
                case (key, value) =>
                  if( value.word != None){
                    print("\t" + key)
                    println("\t aux\t"
                      + aux.get.toLowerCase
                      + "\tvalue\t" + value.word.get.toLowerCase)



                    val chars = value.word.get.toCharArray
                    for (c <- chars) {
                      val check = c.toLower

                      if (check == key){
                        print("-" + c + "-")
                        node.counter +=1
                        value.counter = 1
                      }

                    }

                    //value.counter += 1
                  }
              }
              println()
            }
            /*
            // node.children.foreach(p => println(">>> key=" + p._1 + ", value=" + p._2))
            //println("********" )
          **/

          }  )
        foreachHelper(nodes.flatMap(node => node.children.values): _*)

      }
    }

    foreachHelper(this)
  }

  /*
  * De Parametro le paso la secuencia a predecir o una letra
  *
  * Idea: Itero todo el arbol
  * me coloco en el que tenga mas hijos
  * busco el que tenga mayor counter
  * lo devuelvo con su valor
  *
  * */


  def predictNextPage[U]( param: String ): String = {

    var currentIndex:Int    = 0
    var nextSymbol:String   = ""
    val resultFindBP        = findByPrefix(param)
    val lengthFBP:Int       = resultFindBP.length
    val random              = new Random
    var countPosibility:Int = 0
    val stack               = Stack[String]()
    val alphabet            = Stack[String]()
    var maxProbability:Int  = 0


    //,"R","S","T", "U","V","W","X","Y","Z")
    alphabet.push("A","B","C","D","E","F","G","H","I","J",
      "K","L","M","N","O","P","Q");


    // CUANDO PREGUNTAN POR EPSILON DEBO ENTREGAR DEVOLVERME A LA RAIZ
    // Y PREGUNTAR POR EL SIGUIENTE SIMBOLO CON MEJOR FRECUENCIA

    /**
     * THIRD CONDITION OR:
     * CUANDO ENCUENTRO UN NODO QUE NO TIENE HIJOS Y ESTA YA EN EL FINAL O ES UNA
     * RAMA NO COMPLETA O UN NODO INTERMEDIO.
     */


    if( resultFindBP.length == 1 ){
      nextSymbol = alphabet(random.nextInt(alphabet.length))
      var maxProbabilityChildsAfterEpsilon: Int = 0
      var afterEpsilonNodeWithMoreFreq:String = ""

      def helperEpsilon( nodes: TrieNode) = {
        println("HELPER EPSILON CHILD"+ nodes.children.toString() )
        for(  ch <- nodes.children  ){
          if ( ch._2.counter >  maxProbabilityChildsAfterEpsilon && ch._2.word.isDefined ){
            maxProbabilityChildsAfterEpsilon = ch._2.counter
            afterEpsilonNodeWithMoreFreq = ch._2.word.get
          }
        }
      }
      helperEpsilon(this )
      nextSymbol = afterEpsilonNodeWithMoreFreq

    }


    if( param.length == 0 || param =="" ){
      nextSymbol = alphabet(random.nextInt(alphabet.length))
      var maxProbabilityChildsAfterEpsilon: Int = 0
      var afterEpsilonNodeWithMoreFreq:String = ""

      def helperEpsilon( nodes: TrieNode) = {
         println("HELPER EPSILON CHILD"+ nodes.children.toString() )
        for(  ch <- nodes.children  ){
            if ( ch._2.counter >  maxProbabilityChildsAfterEpsilon && ch._2.word.isDefined ){
              maxProbabilityChildsAfterEpsilon = ch._2.counter
              afterEpsilonNodeWithMoreFreq = ch._2.word.get
            }
        }
      }
      helperEpsilon(this )
      nextSymbol = afterEpsilonNodeWithMoreFreq
    }


    // CASOS QUE SE ENCUENTRAN DENTRO DEL TREI (INNERS NODOS)
    if (param.length > 0) {


      var maxProbabilityChilds: Int = 0
      val stackEquiprobable = Stack[String]()


      pathTo(param) match {
        case Some(param) => {
          val current = param.last

          if(  current.children.size > 1   ){
            maxProbability = current.children.head._2.counter
          }else{
            maxProbability = 0
          }


          for (n <- current.children) {
            println( n._2.word.get )

            // CASO EQUIPROBABLE - fill data
            if (n._2.counter == maxProbability) {
              maxProbability = n._2.counter
              println( ">>>>>>>"+n._2.word.get.stripPrefix(current.word.get)    )
              stackEquiprobable.push(n._2.word.get.stripPrefix(current.word.get))
            }

            // CASO SIMPLE - devolver solo el que tenga mayor probabilidad
            if (n._2.counter > maxProbability) {
              maxProbability = n._2.counter
              nextSymbol = n._2.word.get.stripPrefix(current.word.get)
            }

            // Si tengo mas de 2 evento equiprobables devuelvo solo 1 dentro de los candidatos
            if (stackEquiprobable.size > 1 ){
              println("stack"+  stackEquiprobable.toString() + "length "+stackEquiprobable.size     )
              nextSymbol = stackEquiprobable(random.nextInt(stackEquiprobable.length));
              //stackEquiprobable.clear()
            }


            ///for( s <- stackEquiprobable) println( s );

          }
        }
        // Faltaría un caso en que la consulta no se encuentre

        case None => {
          println(  "No hay info para este evento"+ findByPrefix(param)    );

          var maxProbabilityChildsAfterEpsilon: Int = 0
          var afterEpsilonNodeWithMoreFreq:String = ""

          def othercaseHelper(nodes: TrieNode) ={
            for(  ch <- nodes.children  ){
              if ( ch._2.counter >  maxProbabilityChildsAfterEpsilon && ch._2.word.isDefined ){
                maxProbabilityChildsAfterEpsilon = ch._2.counter
                afterEpsilonNodeWithMoreFreq = ch._2.word.get

                println("HELPER othercaseHelper CHILD"+ nodes.children.toString() +"\t\t"+ch)
                nextSymbol = afterEpsilonNodeWithMoreFreq
              }
            }


          }
          othercaseHelper(this)


        }

      }


      println(">>>> NODO INTERMEDIO CON MAS DE UN HIJO query: " + param + "  predict: " + nextSymbol)
    }




    stack.clear()
    //println(  ">>> predictTo:\t\t what's the next?   "+ param+ "\t ResultPredict: "+ nextSymbol.last.toString +"\t length:  "+ nextSymbol.length+ " of "+nextSymbol )
    //println(  "TRIE \t\t>>>  what's the nextsymbol ?: "+ param+ "\t ResultPredict= "+ nextSymbol+ "\t" )

    nextSymbol
  }



  // Retornar el siguiente simbolo con mayor probabilidad
  def getNodeBySymbol( word : String )  = {
    println("--------------------------- getNodeBySymbo: "+word+" -------------------" )

    var aux:Int = 0
    var nextNode:TrieNode = null
    val random            = new Random


    pathTo(word) match {

      case Some(path) => {
        var index        =  path.length - 1
        var continue     = true
        path(index).word = None

        while ( index > 0 && continue ) {
          val current = path(index) // current node


          //Necesito verificar si el nodo contiene un simbolo ono
          if (current.word.isDefined) {
             println(".>>>> current word IF  para iteracion en ??  "+ current  )
            continue = false

          } else {

            val parent = path(index - 1) // El Padre del nodo con mayo probabilidad


              //actualizo al que tenga el mejor counter
              if (current.counter > aux  ){
                //aux = current.counter // actualizo al actual
                nextNode = current
                //println("Siguiente simbolo con mayor probabilidad dado "+word + " es: \t"+ current.toString() )


                // Cuando tengo mas de un hijo con probabilidades equiprobables o
                if( current.children.size > 0 ){
                    //recorro todos los nodos
                    for( i <- 0 until current.children.size ){
                      if( current.children.toList(i)._2.counter > aux   ){

                        aux = current.children.toList(i)._2.counter
                        nextNode = current.children.toList(i)._2
                        println ("urrent.children(0)    >>< "+  current.children.toList(i)  )
                      }

                    }
                }


              }


            index -= 1
          }
        }

        true
      }
      case None => false
    }

    println( "\n\n\nEl siguiente nodo acorde a la función es: "+ nextNode )

  }


  // Tendria que hacer un metodo que dado Epsilon me retorne el siguiente simbolo con mayor probabilidad.
  def numberOfNodes() = {
    print("numnber of nodes ");

    var counter:Int = 0

    def foreachHelper(nodes: TrieNode*): Unit = {
      if (nodes.size != 0) {
        nodes.foreach(
          node =>{
            counter +=1
          }  )
        foreachHelper(nodes.flatMap(node => node.children.values): _*)

      }
    }
    foreachHelper(this)

    print (">>>> "+ counter+"\n")
  }


  def printHeigthTrieNode[U](f: String => U): Unit = {
    print(" Triee Height:>>>>> ")
    var height:Int = 0
    def foreachHelper(nodes: TrieNode*): Unit = {
      if (nodes.size != 0) {

        height +=1

        foreachHelper(nodes.flatMap(node => node.children.values): _*)

      }
    }
    foreachHelper(this)
    print("\t"+height+" levels"   );


  }




  /*
  *@TODO:
  */
  def clearTree()  ={

  }




}

