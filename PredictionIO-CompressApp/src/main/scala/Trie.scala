package cl.jguzman.piocompressapp.trie

import scala.annotation.tailrec
import scala.collection.JavaConverters._
import scala.collection.mutable
import scala.collection.mutable.ListBuffer
import scala.util.control.Breaks._



object Trie {
  def apply() : Trie = new TrieNode()
}

sealed trait Trie extends Traversable[String] {

  def append(key : String)
  def findByPrefix(prefix: String): scala.collection.Seq[String]
  def contains(word: String): Boolean
  def remove(word : String) : Boolean

};

protected [trie] class TrieNode(val char:   Option[Char] = None,
                             var word:   Option[String] = None,
                             var counter:Int= 0 ) extends Trie {

  var trieHeigth = 0

  protected[trie] val children: mutable.Map[Char, TrieNode] = new java.util.TreeMap[Char, TrieNode]().asScala

  override def  append(key: String) = {


    @tailrec def appendHelper(node: TrieNode, currentIndex: Int): Unit = {

      if (currentIndex == key.length) {
        //System.out.println( "IF "+currentIndex+" == "+key.length+" - "+node.word+"\t "+node.counter )
        node.word     = Some(key)
      }else{

        val char      = key.charAt(currentIndex).toLower
        val result    = node.children.getOrElseUpdate(char, { new TrieNode(Some(char)) })


        node.counter  += 1
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

  override
  def  remove(word : String) : Boolean = {

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

  protected[trie] def pathTo( word : String ) : Option[ListBuffer[TrieNode]] = {

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

  override def  toString() : String = s"Trie(char=${char},word=${word},counter=${counter}})"

  def printTree[U](f: String => U): Unit = {
    println("epsilon");
    @tailrec def foreachHelper(nodes: TrieNode*): Unit = {
      if (nodes.size != 0) {
        //println("\tSZ"+nodes.size )
        println()
        println("--|")

        nodes.foreach(node =>{ for(i <- 0 to node.children.size ){print("    ")}
          print(" "+node.children.size+"_(" )
          node.word.foreach(f)
          print(")#"+node.counter )
        }  )
        foreachHelper(nodes.flatMap(node => node.children.values): _*)

      }
    }

    foreachHelper(this)
  }

  /*
  *@TODO: Me faltan estas ideas que pueden ser utiles
  */
  def clearTree()  ={

  }

  def getFirstSymbol() ={

  }

  def setAlphabet() ={

  }


}

