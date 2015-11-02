package trie

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

}

private[trie] class TrieNode(val char:   Option[Char] = None,
                             var word:   Option[String] = None,
                             var counter:Int= 0 ) extends Trie {

  private[trie] val children: mutable.Map[Char, TrieNode] = new java.util.TreeMap[Char, TrieNode]().asScala

  var trieHeigth = 0

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

  private[trie] def pathTo( word : String ) : Option[ListBuffer[TrieNode]] = {

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

  def   imprime[U](f: String => U): Unit = {
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


}

object Run extends App {

  // Initialize a dictonary by empty phrase
  val trie = new TrieNode()

  val listaValores = List("A","B","R","A","C","A","D","A","B","R","A")
  //val listaValores = List("A","B","R","AC","AD","AB","RA","RAB","RABA","RABZ")

  for( i <- listaValores){
    //println( i )
   // trie.append(i)
  }


  println("::::::::::::::::::::\n\n")

  /* trie.foreach( e => println( e.toString ) )

  println( trie.contains("AB")  )
  println( trie.init  )
  println( trie.children.tail  )
  println( trie.children.last  )
  */

  val lz78 = {

    var tmpStr = ""

    // pass a function to the breakable method
    breakable {
      for (i <- 0 to listaValores.size - 1) {


        println("X es: " + listaValores(i))


        if (trie.contains(listaValores(i)) == true) {
          print("esta en el diccionario y X es: " + listaValores(i) + "\n")
          Thread sleep 1000

          if ((i + 1) >= listaValores.size) {
            println("value de i+1 es" + (i + 1))
            break
          }


          tmpStr += listaValores(i) + listaValores(i + 1)

          println("tmpStr " + tmpStr)

          if (tmpStr.length > 1) trie.append(tmpStr)

          //reset tmp
          tmpStr = ""


        } else {
          trie.append(listaValores(i))
          tmpStr = ""
        }





        println()
      }

    }



  }

  println("::::::::::::::::::::\n\n")






  trie.imprime( t => print( t ) )
  println(  )

  /*println("trie...MIN :::" +trie.min )
   println("trie...HEAD :::" +trie.head )
   println("trie...LAST :::" +trie.last )
   for( nodo <- trie )      println( nodo.)


  println("trie children::" )
  trie.children.keys.foreach{ i =>
                print("Key " + i +"\t")
                println("Value "+ trie.children(i) )
                  }
  println(trie.children.toList.toString() )
  */


  println("::::::::::::::::::::")

  trie.foreach( n => {
      //println( n.length )
    //print( n.head + " - " )
    print( n + " - " )


  });println()

  //println(  trie.children.toString() )

  print(" Find By Prefix:: "); println( trie.findByPrefix("AB") )

  println("path To ::")
  for(it <- trie.pathTo("RA")){
    print( it )
    print(" - ")
  }




}