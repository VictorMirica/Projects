# Generated from TuringMachine.g4 by ANTLR 4.9.2
from antlr4 import *
from io import StringIO
import sys
if sys.version_info[1] > 5:
    from typing import TextIO
else:
    from typing.io import TextIO



def serializedATN():
    with StringIO() as buf:
        buf.write("\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\13")
        buf.write("d\b\1\4\2\t\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7")
        buf.write("\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t\13\4\f\t\f\4\r\t\r\4\16")
        buf.write("\t\16\4\17\t\17\4\20\t\20\3\2\3\2\3\3\3\3\3\4\3\4\3\5")
        buf.write("\3\5\3\6\3\6\3\7\3\7\3\7\5\7/\n\7\3\b\3\b\5\b\63\n\b\3")
        buf.write("\t\6\t\66\n\t\r\t\16\t\67\3\t\3\t\3\n\6\n=\n\n\r\n\16")
        buf.write("\n>\3\13\3\13\3\13\5\13D\n\13\3\f\3\f\3\r\3\r\3\r\3\r")
        buf.write("\7\rL\n\r\f\r\16\rO\13\r\3\16\3\16\3\16\3\16\7\16U\n\16")
        buf.write("\f\16\16\16X\13\16\3\17\5\17[\n\17\3\17\3\17\5\17_\n\17")
        buf.write("\3\20\3\20\3\20\3\20\2\2\21\3\3\5\4\7\5\t\2\13\2\r\2\17")
        buf.write("\2\21\6\23\7\25\2\27\2\31\b\33\t\35\n\37\13\3\2\7\7\2")
        buf.write("##\')<=BB`a\5\2\62;C\\c|\6\2GGJJNNTT\4\2\13\13\"\"\4\2")
        buf.write("\f\f\17\17\2g\2\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\21")
        buf.write("\3\2\2\2\2\23\3\2\2\2\2\31\3\2\2\2\2\33\3\2\2\2\2\35\3")
        buf.write("\2\2\2\2\37\3\2\2\2\3!\3\2\2\2\5#\3\2\2\2\7%\3\2\2\2\t")
        buf.write("\'\3\2\2\2\13)\3\2\2\2\r.\3\2\2\2\17\62\3\2\2\2\21\65")
        buf.write("\3\2\2\2\23<\3\2\2\2\25C\3\2\2\2\27E\3\2\2\2\31G\3\2\2")
        buf.write("\2\33P\3\2\2\2\35^\3\2\2\2\37`\3\2\2\2!\"\7.\2\2\"\4\3")
        buf.write("\2\2\2#$\7*\2\2$\6\3\2\2\2%&\7+\2\2&\b\3\2\2\2\'(\7,\2")
        buf.write("\2(\n\3\2\2\2)*\7%\2\2*\f\3\2\2\2+/\t\2\2\2,/\5\t\5\2")
        buf.write("-/\5\13\6\2.+\3\2\2\2.,\3\2\2\2.-\3\2\2\2/\16\3\2\2\2")
        buf.write("\60\63\t\3\2\2\61\63\5\r\7\2\62\60\3\2\2\2\62\61\3\2\2")
        buf.write("\2\63\20\3\2\2\2\64\66\5\17\b\2\65\64\3\2\2\2\66\67\3")
        buf.write("\2\2\2\67\65\3\2\2\2\678\3\2\2\289\3\2\2\29:\7\60\2\2")
        buf.write(":\22\3\2\2\2;=\5\17\b\2<;\3\2\2\2=>\3\2\2\2><\3\2\2\2")
        buf.write(">?\3\2\2\2?\24\3\2\2\2@D\t\4\2\2AB\7R\2\2BD\5\17\b\2C")
        buf.write("@\3\2\2\2CA\3\2\2\2D\26\3\2\2\2EF\t\5\2\2F\30\3\2\2\2")
        buf.write("GM\5\25\13\2HI\5\3\2\2IJ\5\25\13\2JL\3\2\2\2KH\3\2\2\2")
        buf.write("LO\3\2\2\2MK\3\2\2\2MN\3\2\2\2N\32\3\2\2\2OM\3\2\2\2P")
        buf.write("Q\7\61\2\2QR\7\61\2\2RV\3\2\2\2SU\n\6\2\2TS\3\2\2\2UX")
        buf.write("\3\2\2\2VT\3\2\2\2VW\3\2\2\2W\34\3\2\2\2XV\3\2\2\2Y[\7")
        buf.write("\17\2\2ZY\3\2\2\2Z[\3\2\2\2[\\\3\2\2\2\\_\7\f\2\2]_\7")
        buf.write("\17\2\2^Z\3\2\2\2^]\3\2\2\2_\36\3\2\2\2`a\7\"\2\2ab\3")
        buf.write("\2\2\2bc\b\20\2\2c \3\2\2\2\f\2.\62\67>CMVZ^\3\b\2\2")
        return buf.getvalue()


class TuringMachineLexer(Lexer):

    atn = ATNDeserializer().deserialize(serializedATN())

    decisionsToDFA = [ DFA(ds, i) for i, ds in enumerate(atn.decisionToState) ]

    COMMA = 1
    OPAREN = 2
    CPAREN = 3
    ALPHABET = 4
    IDENTIFIER = 5
    ACTIONS = 6
    COMMENT = 7
    NEWLINE = 8
    WHITESPACE = 9

    channelNames = [ u"DEFAULT_TOKEN_CHANNEL", u"HIDDEN" ]

    modeNames = [ "DEFAULT_MODE" ]

    literalNames = [ "<INVALID>",
            "','", "'('", "')'", "' '" ]

    symbolicNames = [ "<INVALID>",
            "COMMA", "OPAREN", "CPAREN", "ALPHABET", "IDENTIFIER", "ACTIONS", 
            "COMMENT", "NEWLINE", "WHITESPACE" ]

    ruleNames = [ "COMMA", "OPAREN", "CPAREN", "ANY", "EMPTYCELL", "NSSYMBOL", 
                  "ALPHABET_CHAR", "ALPHABET", "IDENTIFIER", "ACTION", "WS", 
                  "ACTIONS", "COMMENT", "NEWLINE", "WHITESPACE" ]

    grammarFileName = "TuringMachine.g4"

    def __init__(self, input=None, output:TextIO = sys.stdout):
        super().__init__(input, output)
        self.checkVersion("4.9.2")
        self._interp = LexerATNSimulator(self, self.atn, self.decisionsToDFA, PredictionContextCache())
        self._actions = None
        self._predicates = None


