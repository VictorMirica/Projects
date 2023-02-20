import scala.collection.mutable

trait AST[A] {

    def run(): Nfa[A]
}

// Diferite tipuri de 'noduri' valabile AST-ului

class valueAST[A](initName: A, finalName :A, alphabet: Set[Char], symbol: Char) extends AST[A] {
    def run(): Nfa[A] = {
        val initState: State[A] = new State[A](initName, List[(Char, A)]())
        val finalState: State[A] = new State[A](finalName, List[(Char, A)]())
        initState.addPath(symbol, finalState.getName)

        val states: Set[State[A]] = Set(initState, finalState)
        new Nfa[A](states, alphabet, initName, Set[A](finalName))
    }
}

class voidAST[A](initName: A, alphabet: Set[Char]) extends AST[A]{
    def run(): Nfa[A] = {
      val initState: State[A] = new State[A](initName, List[(Char, A)]())

      val states: Set[State[A]] = Set(initState)
      new Nfa[A](states, alphabet, initName, Set())
    }
}


class unionAST[A](initName: A, finalName: A, alphabet: Set[Char],left: AST[A], right: AST[A]) extends AST[A]{
    def run(): Nfa[A] = {
        if(left.isInstanceOf[voidAST[A]])
            right.run()
        else if(right.isInstanceOf[voidAST[A]])
            left.run()
        else {
            val initState: State[A] = new State[A](initName, List[(Char, A)]())
            val finalState: State[A] = new State[A](finalName, List[(Char, A)]())

            val leftNfa: Nfa[A] = left.run()
            val rightNfa: Nfa[A] = right.run()

            initState.addPath('ɛ', leftNfa.getInitialStateName)
            initState.addPath('ɛ', rightNfa.getInitialStateName)

            leftNfa.getFinalStates.foreach(x => x.addPath('ɛ', finalState.getName))
            rightNfa.getFinalStates.foreach(x => x.addPath('ɛ', finalState.getName))

            val states: Set[State[A]] = Set(initState, finalState) ++ leftNfa.getAllStates ++ rightNfa.getAllStates
            new Nfa[A](states, alphabet, initName, Set[A](finalName))
        }
    }
}

class concatAST[A](alphabet: Set[Char], left: AST[A], right: AST[A]) extends AST[A] {
    def run(): Nfa[A] = {
        if (left.isInstanceOf[voidAST[A]] || right.isInstanceOf[voidAST[A]])
            null
        else {
            val leftNfa: Nfa[A] = left.run()
            val rightNfa: Nfa[A] = right.run()

            leftNfa.getFinalStates.foreach(x => x.addPath('ɛ', rightNfa.getInitialState.getName))

            val states: Set[State[A]] = Set() ++ leftNfa.getAllStates ++ rightNfa.getAllStates
            new Nfa[A](states, alphabet, leftNfa.getInitialStateName, rightNfa.getFinalStatesNames)
        }
    }
}

class starAST[A](initName: A, finalName: A, alphabet: Set[Char], child: AST[A]) extends AST[A]{
    def run(): Nfa[A] = {
        if(child.isInstanceOf[voidAST[A]])
            null
        else {
            val initState: State[A] = new State[A](initName, List[(Char, A)]())
            val finalState: State[A] = new State[A](finalName, List[(Char, A)]())

            val childNfa: Nfa[A] = child.run()

            initState.addPath('ɛ', childNfa.getInitialStateName)
            initState.addPath('ɛ', finalState.getName)

            childNfa.getFinalStates.foreach(x => {
                x.addPath('ɛ', finalState.getName)
                x.addPath('ɛ', childNfa.getInitialStateName)
            })

            val states: Set[State[A]] = Set(initState, finalState) ++ childNfa.getAllStates
            new Nfa[A](states, alphabet, initName, Set[A](finalName))
        }
    }
}

class plusAST[A](initName: A, finalName: A, alphabet: Set[Char], child: AST[A]) extends AST[A] {
  def run(): Nfa[A] = {
    if(child.isInstanceOf[voidAST[A]])
      null
    else {
      new concatAST[A](alphabet, child, new starAST[A](initName, finalName, alphabet, child)).run()
    }
  }
}

class maybeAST[A](initName: A, finalName: A, initName2: A, finalName2: A, alphabet: Set[Char], child: AST[A]) extends AST[A] {
  def run(): Nfa[A] = {
    if (child.isInstanceOf[voidAST[A]])
      null
    else {
      new unionAST[A](initName, finalName, alphabet, child, new valueAST[A](initName2, finalName2, alphabet, 'ɛ')).run()
    }
  }
}

object AST {

  def buildAST[A](types: mutable.Queue[String], names: mutable.Queue[A], alphabet: Set[Char]): AST[A] = {
    types.dequeue() match {
      case "UNION" => new unionAST[A](names.dequeue(), names.dequeue(), alphabet,
        buildAST[A](types, names, alphabet), buildAST[A](types, names, alphabet))
      case "CONCAT" => new concatAST[A](alphabet, buildAST[A](types, names, alphabet), buildAST[A](types, names, alphabet))
      case "STAR" => new starAST[A](names.dequeue(), names.dequeue(), alphabet, buildAST[A](types, names, alphabet))
      case "PLUS" => new plusAST[A](names.dequeue(), names.dequeue(), alphabet, buildAST[A](types, names, alphabet))
      case "MAYBE" => new maybeAST[A](names.dequeue(), names.dequeue(), names.dequeue(), names.dequeue(), alphabet, buildAST[A](types, names, alphabet))
      case "void" => new voidAST[A](names.dequeue(), alphabet)
      case "eps" => new valueAST[A](names.dequeue(), names.dequeue(), alphabet, 'ɛ')
      case default => new valueAST[A](names.dequeue(), names.dequeue(), alphabet, default(0))
    }
  }
}
