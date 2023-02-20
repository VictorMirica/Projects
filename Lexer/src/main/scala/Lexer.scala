import scala.collection.mutable

case class Lexer (spec: String) {

  /*
    This is the main function of the lexer, it splits the given word into a list of lexems
    in the format (LEXEM, TOKEN)
  */
  def lex(word: String): Either[String,List[(String,String)]] = {

    // Construiesc o corelatie de tipul (REGEX, TOKEN), din spec
    val regexes1 : Array[(String, String)] = spec.split(";\n").
                                           map(x => x.split(": ")).
                                           map{case Array(x1: String, x2:String) => (x2, x1)}

    val regexes: mutable.LinkedHashMap[String, String] = new mutable.LinkedHashMap[String, String]
    regexes1.foreach(x => regexes += (x._1 -> x._2))

    // Convertesc fiecare regex intr-un NFA
    val nfas:  mutable.LinkedHashMap[Nfa[Int], String] = regexes.map(x => (Nfa.fromPrenex(Regex.toPrenex(x._1)), x._2))

    // Construiesc NFA-ul unic
    // Schimb numele starilor pentru nfa-urile create mai sus
    var stateName : Int = 2
    nfas.foreach(x => {
      // Pentru fiecare nfa imi generez un map care sa reprezinte
      // noile nume ale starilor
      val newNames: mutable.LinkedHashMap[Int, Int] = new mutable.LinkedHashMap[Int, Int]()
      x._1.getStates.foreach(x => {
        newNames += (x -> stateName)
        stateName += 1
      })

      // Schimb numele starilor din nfa
      x._1.setInitState(newNames(x._1.getInitialStateName))

      var newFinalStates : Set[Int] = Set()
      x._1.getFinalStatesNames.foreach(x => newFinalStates += newNames(x))
      x._1.setFinalStates(newFinalStates)

      x._1.getAllStates.foreach(y => {
        y.setName(newNames(y.name))

        var newPathsNames : List[(Char, Int)] = List()
        y.paths.foreach(x => newPathsNames = (x._1, newNames(x._2))::newPathsNames)
        y.setPaths(newPathsNames)
      })
    })

    var states: Set[State[Int]] = Set()
    var alphabet: Set[Char] = Set()
    var finalStates: Set[Int] = Set()

    // Creez noua stare initiala si o introduc in states
    val initState: State[Int] = new State(1, List())
    nfas.foreach(x => initState.addPath('ɛ', x._1.getInitialStateName))
    states += initState

    // Adaug intr-un singur set toate starile din nfa-urile corespunzatoare fiecarui token
    nfas.foreach(x => {
      states ++= x._1.getAllStates
      alphabet ++= x._1.getAlphabet
      finalStates ++= x._1.getFinalStatesNames
    })

    val nfa: Nfa[Int] = new Nfa[Int](states, alphabet, 1, finalStates)

    //Imi creez un map care asociaza starile finale corespunzatoare din NFA cu token-urile
    val nfaFinalStatesToken: mutable.LinkedHashMap[Int, String] = new mutable.LinkedHashMap[Int, String]()
    nfas.foreach(x => x._1.getFinalStatesNames.foreach(y => nfaFinalStatesToken += (y -> x._2)))

    // Transform NFA-ul intr-un DFA
    val dfa: Dfa[Int] = Dfa.getDfaFromNfa(nfa)

    //Imi creez un map care asociaza starile finale corespunzatoare din DFA cu token-urile
    val dfaFinalStatesToken: mutable.LinkedHashMap[Int, Set[String]] = new mutable.LinkedHashMap[Int, Set[String]]()
    dfa.nfaFinalStates.foreach(x => {
      var set: Set[String] = Set()
      x._2.foreach(y => if (nfaFinalStatesToken.contains(y)) set += nfaFinalStatesToken(y))
      dfaFinalStatesToken += (x._1 -> set)
    })

    var output: List[(String,String)] = List()
    var startSubstring: Int = 0
    var lastSubstring: Int = 0
    var errorLine: Int = 0


    // Rulam dfa-ul pe subsiruri, pana cand ajungem la finalul stringului complet
    while (lastSubstring < word.length) {

      var lastFinalState: Int = 0
      var lastCharacter: Int = -1
      var currentStates: Set[Int] = Set(dfa.getInitialState)
      var index: Int = lastSubstring

      if (word.charAt(index) == '\n') {
        errorLine += 1
      }

      // Mergem din caracter in caracter, pe subsirul curent
      while (index < word.length) {

        var auxSet: Set[Int] = Set()
        currentStates.foreach(x => {
          if (x != 0) {
            val next: Int = dfa.next(x, word.charAt(index))
            auxSet += next
          }
        })

        currentStates = auxSet


        // Daca am ajunsin sinkstate, trebuie sa trimitem o eroare
        if (currentStates.isEmpty) {
          if (lastCharacter == -1)
            lastCharacter = index - 1
        }

        index += 1

        // In cazul in care avem o stare finala, inseamna ca avem cel putin un token
        currentStates.foreach(x => if (dfa.isFinal(x)) {
          lastFinalState = x
          lastSubstring = index
        })
      }

      // Avem o eroare, deorece nu am ajuns la nici o stare finala
      if (lastFinalState == 0) {
        // In cazul in care nu am terminat cuvantul, sunt la ultimul caracter , dar nu mai am in ce stari sa ma duc
        if (currentStates.contains(0))
          return Left("No viable alternative at character " + (index - 1) + ", line " + errorLine)

        // In cazul in care nu am terminat cuvantul, dar nu mai am in ce stari sa ma duc
        if (currentStates.isEmpty)
          return Left("No viable alternative at character " + lastCharacter + ", line " + errorLine)

        // Cazul in care am terminat cuvantul fara a ajunge intr-o stare finala
        return Left("No viable alternative at character EOF, line " + errorLine)
      }

      output :+= (word.slice(startSubstring, lastSubstring), dfaFinalStatesToken(lastFinalState).last)
      startSubstring = lastSubstring

    }

    Right(output)
  }
}


