/*
 * usage example
 *
 * scalac Main.scala&&scala HelloWorld
 */

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
}
