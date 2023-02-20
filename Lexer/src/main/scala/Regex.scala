import scala.collection.mutable

object Regex {

  // Functie pentru Syntactic sugars
  def processSyntacticSugar(c: Char): List[Either[Char,Char]] = {
    var ret: List[Either[Char, Char]] = List()
    ret :+= Left('(')

    c match {
      case '0' =>
        for (i <- '0' to '9') {
          ret :+= Right(i)
          ret :+= Left('|')
        }

      case 'a' =>
        for (i <- 'a' to 'z') {
          ret :+= Right(i)
          ret :+= Left('|')
        }

      case 'A' =>
        for (i <- 'A' to 'Z') {
          ret :+= Right(i)
          ret :+= Left('|')
        }
    }

    ret = ret.dropRight(1)
    ret :+= Left(')')
    ret
  }
  /*
    This function should:
    -> Classify input as either character(or string) or operator
    -> Convert special inputs like [0-9] to their correct form
    -> Convert escaped characters
  */

  // Right -> Character
  // Left -> Operator
  def preprocess(s:List[Char]): List[Either[Char,Char]] = {
    var ret: List[Either[Char, Char]] = List()
    var index: Int = 0

    while (index < s.length) {
      val c: Char = s(index)

      c match {

        // Escapare
        case '\'' =>
          if (s(index + 1) == '\\' && s(index + 2) == 'n') {
            ret :+= Right('\n')
            index += 4
          } else if (s(index + 1) == '\\' && s(index + 2) == 't')  {
            ret :+= Right('\t')
            index += 4
          } else {
            // In cazul in care am escapate unele caractere folosite
            // cum ar fi + sau *, le inlocuiesc cu alt caracter,
            // ca la urma sa le schimb inapoi
            if (s(index + 1) == '+') {
              ret :+= Right('~')
            } else if (s(index + 1) == '*') {
              ret :+= Right('`')
            } else if (s(index + 1) == '(') {
              ret :+= Right('{')
            } else if (s(index + 1) == ')') {
              ret :+= Right('}')
            } else {
              ret :+= Right(s(index + 1))
            }
            index += 3
          }

        // Syntactic sugar
        case '[' =>
          var e: List[Either[Char, Char]] = List()
          val h: Char = s(index + 1)
          h match {
            case '0' => e ++= processSyntacticSugar('0')
            case 'a' => e ++= processSyntacticSugar('a')
            case 'A' => e ++= processSyntacticSugar('A')
          }
          index += 5

          // Putem avea '+' sau '?' dupa un syntactic sugar
          if (index < s.length) {
            val h: Char = s(index)
            h match {
              case '+' =>
                ret ++= e
                ret ++= e :+ Left('*')
                index += 1
              case '?' =>
                ret :+= Left('(')
                ret ++= e :+ Left('|') :+ Right('ɛ')
                ret :+= Left(')')
                index += 1
              case _ => ret ++= e
            }
          } else {
            ret ++= e
          }


        // Paranteze, care pot fi urmate de '+' sau '?'
        // In caz de '?' mai am nevoie de inca un set de paranteze
        // pentru (e u ɛ)
        case '(' =>
          ret :+= Left('(')
          index += 1

          var toProcess: List[Char] = List()
          var openParantheses: Int = 1
          while (openParantheses != 0) {
            if (s(index) == '(') {
              openParantheses += 1
            }
            if (s(index) == ')') {
              openParantheses -= 1
            }
            if (openParantheses != 0)
              toProcess :+= s(index)
            index += 1
          }

          var e: List[Either[Char, Char]] = preprocess(toProcess) :+ Left(')')

          if (index < s.length) {
            val h: Char = s(index)
            h match {
              case '+' =>

                ret ++= e :+ Left('(')
                ret ++= e :+ Left('*')
                index += 1
              case '?' =>
                ret :+= Left('(')
                ret ++= e :+ Left('|') :+ Right('ɛ')
                ret :+= Left(')')
                index += 1
              case _ => ret ++= e
            }
          } else {
            ret ++= e
          }


        // Cazul in care avem + sau ? pe un singur caracter (nu au aparut paranteze sau syntactic sugars)
        case '+' =>
          ret ++= Nil :+ Right(s(index - 1)) :+ Left('*')
          index += 1
        case '?' =>
          ret = ret.dropRight(1)
          ret :+= Left('(')
          ret ++= Nil :+ Right(s(index - 1)) :+ Left('|') :+ Right('ɛ')
          ret :+= Left(')')
          index += 1


        case '*' =>
          ret :+= Left('*')
          index += 1
        case '|' =>
          ret :+= Left('|')
          index += 1
        case default =>
          // test in cazul in care avem sirul "eps" care reprezinta epsilon ('ɛ')
          if (index + 2 < s.length && s(index) == 'e' && s(index + 1) == 'p' && s(index + 2) == 's') {
            ret :+= Right('ɛ')
            index += 3
          } else {
            ret :+= Right(default)
            index += 1
          }
      }
    }
    ret
  }

  // Precedenta operanzilor
  def getPrecedence(c: Char): Int = {
    c match {
      case '*' => 2
      case '+' => 1
      case '|' => 0
    }
  }

  // In continuare, voi reprezenta in stiva de operanzi
  // concat prin simbolul '+'
  // Transform simbolurile in stringurile respective
  def formatPrenex(s: String): String = {
    var ret: String = ""

    var index: Int = 0
    while (index < s.length) {
      s(index) match {
        case '|' => ret += "UNION "
        case '+' => ret += "CONCAT "
        case '*' => ret += "STAR "
        case '~' => ret += "+ "
        case '`' => ret += "* "
        case '{' => ret += "( "
        case '}' => ret += ") "
        case default => ret += (default.toString + " ")
      }
      index += 1
    }

    ret.dropRight(1)
    ret
  }

  // Verificam daca trebuie sa introducem operatorul CONCAT,
  // care va fi reprezentat de +, dar in forma initiala acesta
  // nu exista
  // (ab = a+b)
  def testForConcat(isConcat: Boolean, operatorStack: mutable.Stack[Char], outputStack: mutable.Stack[Char]) : Unit = {
    if (isConcat) {
      while (operatorStack.nonEmpty && operatorStack.top != ')' && getPrecedence(operatorStack.top) >= getPrecedence('+'))
        outputStack.push(operatorStack.pop)
      operatorStack.push('+')
    }
  }

  // This function should construct a prenex expression out of a normal one.
  def toPrenex(str: String): String = {
    var s: String = ""
    var processedStr: List[Either[Char, Char]] = preprocess(str.toList)

    val outputStack: mutable.Stack[Char] = mutable.Stack()
    val operatorStack: mutable.Stack[Char] = mutable.Stack()
    var isConcat: Boolean = false

    processedStr = processedStr.reverse

    processedStr.foreach(x => {
      if (x.isRight) {
        // Introducem in caracter in stiva de output
        val c: Char = x.merge
        // In acest caz, putem avea concat
        testForConcat(isConcat, operatorStack, outputStack)
        isConcat = true
        outputStack.push(c)
      }

      if (x.isLeft) {
        // Avem un operator
        val c: Char = x.merge

        if (c == ')') {
          // In acest caz, putem avea concat
          testForConcat(isConcat, operatorStack, outputStack)

          operatorStack.push(c)
          isConcat = false

        } else if (c == '(') {
          // Eliminam operatorii din stiva si ii introducem in output
          // pana intampinam paranteza inchisa
          while (operatorStack.nonEmpty && operatorStack.top != ')')
            outputStack.push(operatorStack.pop)
          operatorStack.pop()

          isConcat = true

        } else {
          // Inainte de star, putem avea un concat
          if (c == '*') {
            // In acest caz, putem avea concat
            testForConcat(isConcat, operatorStack, outputStack)
          }
          isConcat = false

          // Introducem operatorii din stiva de operatori in output, pana cand gasim un operator
          // cu o precedenta mai mica sau o paranteza inchisa
          while (operatorStack.nonEmpty && operatorStack.top != ')' && getPrecedence(operatorStack.top) > getPrecedence(c))
            outputStack.push(operatorStack.pop)
          operatorStack.push(c)
        }
      }
    })

    while (operatorStack.nonEmpty)
      outputStack.push(operatorStack.pop)

    outputStack.foreach(x => s += x)
    val ret: String = formatPrenex(s)
    ret

  }
}
