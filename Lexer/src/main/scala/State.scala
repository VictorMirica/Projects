class State[A](var name: A, var paths: List[(Char, A)]) {

  def getName : A = name

  def setName(newName : A) : Unit = this.name = newName

  def setPaths(newNames : List[(Char, A)]) : Unit = this.paths = newNames

  def map[B](f: A => B) : State[B] = {
    new State[B](f(name), paths.map(x => (x._1, f(x._2))))
  }

  def getNextStates(c: Char): Set[A] = {
    var states: Set[A] = Set()
    paths.foreach(x => if (x._1 == c) states += x._2)
    states
  }

  def addPath(c: Char, state: A): Unit = {
    this.paths = (c, state)::paths
  }

}

object State {
  def getStateByName[A](name: A, states: Set[State[A]]) : State[A] = {
    var state: State[A] = null
    states.foreach(x => if (x.getName == name) state = x)
    state
  }
}