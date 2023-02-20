import scala.collection.mutable

class Dfa[A](states: Set[State[A]], alphabet: Set[Char], initialState: A, finalStates: Set[A]) {

  // The following methods are only the methods directly called by the test suite. You can (and should) define more.

  // Un map care coreleaza fiecare stare finala a DFA-ului cu starile finale ale NFA-ului din care este formata
  var nfaFinalStates: mutable.LinkedHashMap[A, Set[A]] = new mutable.LinkedHashMap()

  def map[B](f: A => B) : Dfa[B] = new Dfa[B](states.map(x => x.map(f)), alphabet, f(initialState), finalStates.map(x => f(x)))

  def next(state:A, c: Char): A = {
    val set: Set[A] = State.getStateByName(state, states).getNextStates(c)

    if (set.isEmpty) {
      null.asInstanceOf[A]
    } else {
      set.head
    }
  }

  def accepts(str: String): Boolean = {
    val string: String = str

    var index = 0
    var currentStates: Set[A] = Set(initialState)

    // Merg din stare in stare, pe fiecare caracter din string
    while  (index < string.length) {
      var auxSet: Set[A] = Set()
      currentStates.foreach(x => auxSet += next(x, string.charAt(index)))
      currentStates = auxSet
      if(currentStates.contains(null.asInstanceOf[A]))
        currentStates = Set()
      index += 1
    }

    var ret: Boolean = false
    currentStates.foreach(x => if (isFinal(x)) ret = true)
    ret
  }

  def getStates: Set[A] = {
    var stateNames: Set[A] = Set()
    states.foreach(x => stateNames += x.getName)
    stateNames
  }

  def getAllStates: Set[State[A]] = this.states

  def getFinalStatesNames: Set[A] = this.finalStates

  def getInitialState: A = this.initialState

  def isFinal(state: A): Boolean = finalStates.contains(state)
}

// This is a companion object to the Dfa class. This allows us to call the method fromPrenex without instantiating the Dfa class beforehand.
// You can think of the methods of this object like static methods of the Dfa class
object Dfa {

  // Metoda care intoarce epsilon-closures ale unui nfa
  def getEpsClosures[A](nfa: Nfa[A]) : Map[A, Set[A]] = {
    var map: Map[A, Set[A]] = Map()

    nfa.getStates.foreach(x => {
      var set: Set[A] = nfa.next(x, 'ɛ')
      set += x

      map += (x -> set)
    })

    map
  }

  // O functie care construieste numele unei functii din dfa
  // Preiau toate numele starilor din care este formata noua stare de dfa
  // le concatenez intr-un string, si creez hashcode-ul
  def buildStateName[A](states: Set[A]): Int = {
    var stateStr: String = ""
    states.foreach(x => stateStr += x.toString)
    stateStr.hashCode
  }

  def getDfaFromNfa(nfa: Nfa[Int]): Dfa[Int] = {
    val epsClosures: Map[Int, Set[Int]] = getEpsClosures(nfa)

    var states: Set[State[Int]] = Set()
    var finalStates: Set[Int] = Set()
    var alphabet: Set[Char] = nfa.getAlphabet

    // In alfabetul DFA-ului, nu avem si epsilon ('ɛ')
    alphabet -= 'ɛ'

    val nfaFinalStates: mutable.LinkedHashMap[Int, Set[Int]] = new mutable.LinkedHashMap()
    // Starea initiala a dfa-ului este eps-closure-ul starii initiale ale nfa-ului.
    val initState: Int = buildStateName(epsClosures(nfa.getInitialStateName))
    var currentStates: Set[Int] = epsClosures(nfa.getInitialStateName)
    var currentStateName: Int = initState
    var checkSet: Set[Int] = Set()
    var oldCheckSet: Set[Int] = Set(1)
    val nextState: mutable.Queue[Int] = mutable.Queue(currentStateName)
    val nextCurrentStates: mutable.Queue[Set[Int]] = mutable.Queue(currentStates)

    // Voi adauga stari in Dfa pana cand nu se va mai gasi nici o stare noua
    // de adaugat
    while (!checkSet.equals(oldCheckSet) || nextState.nonEmpty) {

      if (nextState.nonEmpty)
        currentStateName = nextState.dequeue()
      if (nextCurrentStates.nonEmpty)
        currentStates = nextCurrentStates.dequeue()

      oldCheckSet = checkSet
      // Noul state
      var newState: State[Int] = new State[Int](currentStateName, List[(Char, Int)]())

      // Formez lista de tranzitii
      // Pentru fiecare element din alfabet
      // Vad daca pot sa gasesc o stare noua
      // formata din mai multe stari la nfa-ului

      alphabet.foreach(x => {
        var newStates: Set[Int] = Set()
        // Pentru fiecare stare (din fostul nfa) din care
        // este formata starea curenta a dfa-ului,
        // adaug starile pe caracterul curent din alfabet
        // si epsilon closure-urile acestora

        currentStates.foreach(y => {
          var flag: Boolean = false
          State.getStateByName(y, nfa.getAllStates).paths.foreach(c => if (c._1 == x) flag = true)
          if (flag) {
            val nextSet: Set[Int] = nfa.next(y, x)
            newStates ++= nextSet
            nextSet.foreach(y => newStates ++= epsClosures(y))
          }
        })

        // Construiesc numele noii stari si adaug path spre ea
        if (newStates.nonEmpty) {
          currentStateName = buildStateName(newStates)
          newState.addPath(x, currentStateName)

          // Adaug noua stare
          if (!checkSet.contains(currentStateName)) {
            nextState.enqueue(currentStateName)
            nextCurrentStates.enqueue(newStates)
          }

          checkSet += currentStateName
        }
      })
      states += newState

      // Daca orice stare noua adaugata contine o stare finala a nfa-ului, aceasta va fi o stare finala a dfa-ului
      currentStates.foreach(x => if (nfa.getFinalStatesNames.contains(x)) {
        finalStates += newState.getName
        nfaFinalStates += (newState.getName -> currentStates)
      })
    }

    val dfa: Dfa[Int] = new Dfa[Int](states, alphabet, initState, finalStates)
    dfa.nfaFinalStates = nfaFinalStates
    dfa
  }

  def fromPrenex(str: String): Dfa[Int] = {
    // You can add more methods to this object
    val nfa: Nfa[Int] = Nfa.fromPrenex(str)
    getDfaFromNfa(nfa)
  }
}
