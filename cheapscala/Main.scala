/*
 * usage example
 *
 * scalac Main.scala&&scala HelloWorld
 */

trait Tree
object Node extends Tree
class Leaf(value: String) extends Tree

object Huga {
  def bye() = println("Good bye!")
}

class Hoge() {
  def hello() = println("Hello, world!")
}

object HelloWorld extends App {
  val hoge = new Hoge()
  // val hoge = new Hoge()
  /*
   * val hoge = new Hoge()
   */
  hoge.hello()
  Huga.bye()
}
