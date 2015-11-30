package cl.jguzman.piocompressapp



import scala.annotation.tailrec
import scala.collection.JavaConverters._
import scala.collection.mutable
import scala.collection.mutable.ListBuffer
import scala.collection.mutable.Stack

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
               var counter:Int= 0) extends Trie {

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

  override def  toString() : String = s"Trie(char=${char},\t\tpage= ${word},\tcounter= ${counter}})"

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


  /*
  *@TODO:
  *  Need to work here, the primary idea is get the frecuency
  *  of ocurrency for caculate the probability
  * */

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

    println(">>>>>>>>predictNextPage")
    var currentIndex:Int =0
    var nextSymbol:String = ""

    @tailrec def foreachHelper(nodes: TrieNode*): Unit = {
      if (nodes.size != 0) {

        var aux:Int=0
        nodes.foreach(
          node =>{
            var chMatch = param.charAt(currentIndex).toLower

            node.children.get( chMatch ) match {
              case Some(child) =>{
                println(child)
                if (child.counter > aux  ){
                  aux = child.counter
                  nextSymbol = child.word.get
                }

              }
              case None => None
            }
          }
        )
        foreachHelper(nodes.flatMap(node => node.children.values): _*)

      }
    }
    //Se me va fuera de rango
    //currentIndex += 1
    foreachHelper(this)
    println(">>>>>>>>The prediction of the next page is:\t"+ nextSymbol)


    nextSymbol
  }



  /*
  *@TODO:
  */
  def clearTree()  ={

  }




}

