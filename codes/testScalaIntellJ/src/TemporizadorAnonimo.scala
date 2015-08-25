/**
 * Created by jguzman on 23-08-15.
 */


object TemporizadorAnonimo {
  def unaVezPorSegundo(callback: () => Unit) {
    while (true) { callback(); Thread sleep 1000 }
  }
  def main(args: Array[String]) {
    unaVezPorSegundo(
      () => println("El tiempo vuela como una flecha...")
    )
  }
}
