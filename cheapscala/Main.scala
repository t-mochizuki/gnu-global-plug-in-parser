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

class Foo() {
  def fee(l: Int, d: Double): Option[Int] = if (l == 0) None else Some(l)
}

object HelloWorld extends App {
  val hoge = new Hoge()
  // val hoge = new Hoge()
  /*
   * val hoge = new Hoge()
   */
  /// val hoge = new Hoge()
  val c = 'a'
  val s = s"""
hello
world
"""
  hoge.hello()
  Huga.bye()
}
