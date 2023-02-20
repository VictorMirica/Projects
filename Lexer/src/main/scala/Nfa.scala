import scala.collection.mutable

class Nfa[A](states: Set[State[A]], alphabet: Set[Char], var initialState: A, var finalStates: Set[A]) {

  // The following methods are only the methods directly called by the test suite. You can (and should) define more.

  def map[B](f: A => B) : Nfa[B] = new Nfa[B](states.map(x => x.map(f)), alphabet, f(initialState), finalStates.map(x => f(x)))

  def next(state: A, c: Char): Set[A] = {

    // Setul de stari la care am ajuns pe c
    var charSet: Set[A] = Set()
    charSet ++= State.getStateByName(state, states).getNextStates(c)

    // Setul de stari la care am ajuns pe eps
    var epsSet: Set[A] = Set()
    epsSet ++= State.getStateByName(state, states).getNextStates('ɛ')

    var epsSetCopy: Set[A] = Set()
    while (epsSet != epsSetCopy) {
      // Pentru fiecare stare la care am ajuns prin eps, verific daca pot sa ajung intr-o noua stare, pe c
      epsSet.foreach(x => State.getStateByName(x, states).getNextStates(c).foreach(x => charSet += x))
      // Rulez asta pana cand nu se va ma updata setul de stari in care pot ajunge pe eps
      epsSetCopy = epsSet
      epsSet.foreach(x => State.getStateByName(x, states).getNextStates('ɛ').foreach(x => epsSet += x))
    }

    // Pentru fiecare stare in care am ajuns pe c, mai pot sa adaug la starile next
    // doar urmatoarele n stari la care pot ajunge pe eps
    epsSet = Set()
    charSet.foreach(x => State.getStateByName(x, states).getNextStates('ɛ').foreach(x => epsSet += x))
    epsSetCopy = Set()
    while (epsSet != epsSetCopy) {
      epsSetCopy = epsSet
      epsSet.foreach(x => State.getStateByName(x, states).getNextStates('ɛ').foreach(x => epsSet += x))
    }

    charSet ++ epsSet
  }

  def accepts(str: String): Boolean = {

    // In cazul in care stringul este gol, se verifica stringul "ɛ"
    var string: String = str
    if (str.isEmpty) string = "ɛ"

    var index = 0
    var currentStates: Set[A] = Set(initialState)

    // Merg din stare in stare, pe fiecare caracter din string
    while  (index < string.length) {
      var auxSet: Set[A] = Set()
      currentStates.foreach(x => auxSet ++= next(x, string.charAt(index)))
      currentStates = auxSet
      index += 1
    }

    var ret: Boolean = false
    currentStates.foreach(x => if (isFinal(x)) ret = true)
    ret
  }

  def setInitState(newName : A) : Unit = this.initialState = newName

  def setFinalStates(newNames : Set[A]) : Unit = this.finalStates = newNames

  def getStates : Set[A] = {
    var stateNames: Set[A] = Set()
    states.foreach(x => stateNames += x.getName)
    stateNames
  }

  def isFinal(state: A): Boolean = finalStates.contains(state)

  def getInitialState: State[A] = State.getStateByName(initialState, states)

  def getInitialStateName: A = initialState

  def getFinalStates: Set[State[A]] = {
    var ret: Set[State[A]] = Set()
    finalStates.foreach(x => ret += State.getStateByName(x, states))
    ret
  }

  def getFinalStatesNames: Set[A] = finalStates

  def getAllStates: Set[State[A]] = states

  def getAlphabet: Set[Char] = alphabet
}

// This is a companion object to the Nfa class. This allows us to call the method fromPrenex without instantiating the Nfa class beforehand.
// You can think of the methods of this object like static methods of the Nfa class
object Nfa {
  def fromPrenex(str: String): Nfa[Int] = {

    // You can add more methods to this object
    // In stari nfa, tarnzitia pe epsilon se va citi ca tranzitia
    // pe caracterul 'ɛ'
    // In cazul in care elementele (atomii) sunt de forma 'c', dorim
    // sa scapam de ghilimele
    // De asemenea, dorim sa adaugam caracterele spatiu (' ') daca acestea
    // Sunt in ghilimele, deci nu putem sa dam un simplu .split()
    var tokens: Array[String] = Array()
    var tokenString: String = ""
    var addSpace: Boolean = false
    str.foreach(x => {
         if (x == ' ') {
           if (!addSpace) {
             tokens :+= tokenString
             tokenString = ""
             addSpace = true
           } else {
             tokenString :+= x
             addSpace = false
           }
         } else {
           tokenString :+= x
           addSpace = false
         }
    })

    if (addSpace) {
      tokenString :+= ' '
    }
    tokens :+= tokenString

    var tokensaux: Array[String] = Array()
    tokens.foreach(x => tokensaux = tokensaux :+ x.replaceAll("^'|'$", ""))
    tokensaux = tokensaux.filter(_.nonEmpty)
    tokens = tokensaux



    // Daca lista de token-uri este empty, ii vom adauga valoarea " " (spatiu)
    // Deoarece aceasta a fost stearsa de functia split(" ")
    if (tokens.isEmpty)
      tokens = Array(" ")

    //  Maximul de stari va fi lungimea array-ului de token-uri * 4, deoarece
    // cele mai multe stari noi formate dintr-un singur token este 4 (maybe)
    val names: Array[Int] = (1 to (tokens.length * 4)).toArray

    val typesQueue: mutable.Queue[String] = mutable.Queue().enqueueAll(tokens)
    val namesQueue: mutable.Queue[Int] = mutable.Queue().enqueueAll(names)

    // Construiesc alfabetul (acesta trebuia sa contina si epsilon)
    var alphabet: Set[Char] = Set()
    tokens.foreach(x => if (x.length == 1) alphabet += x(0))
    if (tokens.contains("eps")) alphabet += 'ɛ'

    AST.buildAST[Int](typesQueue, namesQueue, alphabet).run()
  }
}






