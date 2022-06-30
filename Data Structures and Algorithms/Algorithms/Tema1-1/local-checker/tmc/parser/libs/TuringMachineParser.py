# Generated from TuringMachine.g4 by ANTLR 4.9.2
# encoding: utf-8
from antlr4 import *
from io import StringIO
import sys
if sys.version_info[1] > 5:
	from typing import TextIO
else:
	from typing.io import TextIO


def serializedATN():
    with StringIO() as buf:
        buf.write("\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3\13")
        buf.write("h\4\2\t\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b")
        buf.write("\t\b\4\t\t\t\4\n\t\n\4\13\t\13\4\f\t\f\4\r\t\r\4\16\t")
        buf.write("\16\3\2\3\2\6\2\37\n\2\r\2\16\2 \3\2\3\2\5\2%\n\2\7\2")
        buf.write("\'\n\2\f\2\16\2*\13\2\3\2\3\2\3\3\3\3\3\4\3\4\3\4\3\4")
        buf.write("\6\4\64\n\4\r\4\16\4\65\3\5\5\59\n\5\3\5\3\5\3\5\3\6\3")
        buf.write("\6\3\7\3\7\3\b\3\b\3\b\3\b\3\b\5\bG\n\b\3\t\3\t\3\t\7")
        buf.write("\tL\n\t\f\t\16\tO\13\t\3\n\3\n\3\n\3\n\3\n\5\nV\n\n\3")
        buf.write("\13\3\13\3\f\3\f\3\r\3\r\3\r\7\r_\n\r\f\r\16\rb\13\r\3")
        buf.write("\16\3\16\5\16f\n\16\3\16\2\2\17\2\4\6\b\n\f\16\20\22\24")
        buf.write("\26\30\32\2\3\3\2\7\b\2d\2\34\3\2\2\2\4-\3\2\2\2\6/\3")
        buf.write("\2\2\2\b8\3\2\2\2\n=\3\2\2\2\f?\3\2\2\2\16A\3\2\2\2\20")
        buf.write("H\3\2\2\2\22P\3\2\2\2\24W\3\2\2\2\26Y\3\2\2\2\30[\3\2")
        buf.write("\2\2\32e\3\2\2\2\34(\7\6\2\2\35\37\7\n\2\2\36\35\3\2\2")
        buf.write("\2\37 \3\2\2\2 \36\3\2\2\2 !\3\2\2\2!$\3\2\2\2\"%\5\6")
        buf.write("\4\2#%\7\t\2\2$\"\3\2\2\2$#\3\2\2\2%\'\3\2\2\2&\36\3\2")
        buf.write("\2\2\'*\3\2\2\2(&\3\2\2\2()\3\2\2\2)+\3\2\2\2*(\3\2\2")
        buf.write("\2+,\7\2\2\3,\3\3\2\2\2-.\7\7\2\2.\5\3\2\2\2/\63\5\16")
        buf.write("\b\2\60\61\5\b\5\2\61\62\7\n\2\2\62\64\3\2\2\2\63\60\3")
        buf.write("\2\2\2\64\65\3\2\2\2\65\63\3\2\2\2\65\66\3\2\2\2\66\7")
        buf.write("\3\2\2\2\679\5\n\6\28\67\3\2\2\289\3\2\2\29:\3\2\2\2:")
        buf.write(";\5\f\7\2;<\5\22\n\2<\t\3\2\2\2=>\7\7\2\2>\13\3\2\2\2")
        buf.write("?@\t\2\2\2@\r\3\2\2\2AF\7\7\2\2BC\7\4\2\2CD\5\20\t\2D")
        buf.write("E\7\5\2\2EG\3\2\2\2FB\3\2\2\2FG\3\2\2\2G\17\3\2\2\2HM")
        buf.write("\7\7\2\2IJ\7\3\2\2JL\7\7\2\2KI\3\2\2\2LO\3\2\2\2MK\3\2")
        buf.write("\2\2MN\3\2\2\2N\21\3\2\2\2OM\3\2\2\2PU\5\24\13\2QR\7\4")
        buf.write("\2\2RS\5\30\r\2ST\7\5\2\2TV\3\2\2\2UQ\3\2\2\2UV\3\2\2")
        buf.write("\2V\23\3\2\2\2WX\5\26\f\2X\25\3\2\2\2YZ\7\7\2\2Z\27\3")
        buf.write("\2\2\2[`\5\32\16\2\\]\7\3\2\2]_\5\32\16\2^\\\3\2\2\2_")
        buf.write("b\3\2\2\2`^\3\2\2\2`a\3\2\2\2a\31\3\2\2\2b`\3\2\2\2cf")
        buf.write("\5\22\n\2df\5\4\3\2ec\3\2\2\2ed\3\2\2\2f\33\3\2\2\2\f")
        buf.write(" $(\658FMU`e")
        return buf.getvalue()


class TuringMachineParser ( Parser ):

    grammarFileName = "TuringMachine.g4"

    atn = ATNDeserializer().deserialize(serializedATN())

    decisionsToDFA = [ DFA(ds, i) for i, ds in enumerate(atn.decisionToState) ]

    sharedContextCache = PredictionContextCache()

    literalNames = [ "<INVALID>", "','", "'('", "')'", "<INVALID>", "<INVALID>", 
                     "<INVALID>", "<INVALID>", "<INVALID>", "' '" ]

    symbolicNames = [ "<INVALID>", "COMMA", "OPAREN", "CPAREN", "ALPHABET", 
                      "IDENTIFIER", "ACTIONS", "COMMENT", "NEWLINE", "WHITESPACE" ]

    RULE_program = 0
    RULE_lsymbol = 1
    RULE_instruction = 2
    RULE_instr_body = 3
    RULE_match_ = 4
    RULE_actions = 5
    RULE_state_def = 6
    RULE_symargs = 7
    RULE_state_ = 8
    RULE_state_name2 = 9
    RULE_state_name = 10
    RULE_args = 11
    RULE_arg = 12

    ruleNames =  [ "program", "lsymbol", "instruction", "instr_body", "match_", 
                   "actions", "state_def", "symargs", "state_", "state_name2", 
                   "state_name", "args", "arg" ]

    EOF = Token.EOF
    COMMA=1
    OPAREN=2
    CPAREN=3
    ALPHABET=4
    IDENTIFIER=5
    ACTIONS=6
    COMMENT=7
    NEWLINE=8
    WHITESPACE=9

    def __init__(self, input:TokenStream, output:TextIO = sys.stdout):
        super().__init__(input, output)
        self.checkVersion("4.9.2")
        self._interp = ParserATNSimulator(self, self.atn, self.decisionsToDFA, self.sharedContextCache)
        self._predicates = None




    class ProgramContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def ALPHABET(self):
            return self.getToken(TuringMachineParser.ALPHABET, 0)

        def EOF(self):
            return self.getToken(TuringMachineParser.EOF, 0)

        def instruction(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(TuringMachineParser.InstructionContext)
            else:
                return self.getTypedRuleContext(TuringMachineParser.InstructionContext,i)


        def COMMENT(self, i:int=None):
            if i is None:
                return self.getTokens(TuringMachineParser.COMMENT)
            else:
                return self.getToken(TuringMachineParser.COMMENT, i)

        def NEWLINE(self, i:int=None):
            if i is None:
                return self.getTokens(TuringMachineParser.NEWLINE)
            else:
                return self.getToken(TuringMachineParser.NEWLINE, i)

        def getRuleIndex(self):
            return TuringMachineParser.RULE_program

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterProgram" ):
                listener.enterProgram(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitProgram" ):
                listener.exitProgram(self)




    def program(self):

        localctx = TuringMachineParser.ProgramContext(self, self._ctx, self.state)
        self.enterRule(localctx, 0, self.RULE_program)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 26
            self.match(TuringMachineParser.ALPHABET)
            self.state = 38
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            while _la==TuringMachineParser.NEWLINE:
                self.state = 28 
                self._errHandler.sync(self)
                _la = self._input.LA(1)
                while True:
                    self.state = 27
                    self.match(TuringMachineParser.NEWLINE)
                    self.state = 30 
                    self._errHandler.sync(self)
                    _la = self._input.LA(1)
                    if not (_la==TuringMachineParser.NEWLINE):
                        break

                self.state = 34
                self._errHandler.sync(self)
                token = self._input.LA(1)
                if token in [TuringMachineParser.IDENTIFIER]:
                    self.state = 32
                    self.instruction()
                    pass
                elif token in [TuringMachineParser.COMMENT]:
                    self.state = 33
                    self.match(TuringMachineParser.COMMENT)
                    pass
                else:
                    raise NoViableAltException(self)

                self.state = 40
                self._errHandler.sync(self)
                _la = self._input.LA(1)

            self.state = 41
            self.match(TuringMachineParser.EOF)
        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class LsymbolContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def IDENTIFIER(self):
            return self.getToken(TuringMachineParser.IDENTIFIER, 0)

        def getRuleIndex(self):
            return TuringMachineParser.RULE_lsymbol

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterLsymbol" ):
                listener.enterLsymbol(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitLsymbol" ):
                listener.exitLsymbol(self)




    def lsymbol(self):

        localctx = TuringMachineParser.LsymbolContext(self, self._ctx, self.state)
        self.enterRule(localctx, 2, self.RULE_lsymbol)
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 43
            self.match(TuringMachineParser.IDENTIFIER)
        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class InstructionContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def state_def(self):
            return self.getTypedRuleContext(TuringMachineParser.State_defContext,0)


        def instr_body(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(TuringMachineParser.Instr_bodyContext)
            else:
                return self.getTypedRuleContext(TuringMachineParser.Instr_bodyContext,i)


        def NEWLINE(self, i:int=None):
            if i is None:
                return self.getTokens(TuringMachineParser.NEWLINE)
            else:
                return self.getToken(TuringMachineParser.NEWLINE, i)

        def getRuleIndex(self):
            return TuringMachineParser.RULE_instruction

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterInstruction" ):
                listener.enterInstruction(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitInstruction" ):
                listener.exitInstruction(self)




    def instruction(self):

        localctx = TuringMachineParser.InstructionContext(self, self._ctx, self.state)
        self.enterRule(localctx, 4, self.RULE_instruction)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 45
            self.state_def()
            self.state = 49 
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            while True:
                self.state = 46
                self.instr_body()
                self.state = 47
                self.match(TuringMachineParser.NEWLINE)
                self.state = 51 
                self._errHandler.sync(self)
                _la = self._input.LA(1)
                if not (_la==TuringMachineParser.IDENTIFIER or _la==TuringMachineParser.ACTIONS):
                    break

        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class Instr_bodyContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def actions(self):
            return self.getTypedRuleContext(TuringMachineParser.ActionsContext,0)


        def state_(self):
            return self.getTypedRuleContext(TuringMachineParser.State_Context,0)


        def match_(self):
            return self.getTypedRuleContext(TuringMachineParser.Match_Context,0)


        def getRuleIndex(self):
            return TuringMachineParser.RULE_instr_body

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterInstr_body" ):
                listener.enterInstr_body(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitInstr_body" ):
                listener.exitInstr_body(self)




    def instr_body(self):

        localctx = TuringMachineParser.Instr_bodyContext(self, self._ctx, self.state)
        self.enterRule(localctx, 6, self.RULE_instr_body)
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 54
            self._errHandler.sync(self)
            la_ = self._interp.adaptivePredict(self._input,4,self._ctx)
            if la_ == 1:
                self.state = 53
                self.match_()


            self.state = 56
            self.actions()
            self.state = 57
            self.state_()
        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class Match_Context(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def IDENTIFIER(self):
            return self.getToken(TuringMachineParser.IDENTIFIER, 0)

        def getRuleIndex(self):
            return TuringMachineParser.RULE_match_

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterMatch_" ):
                listener.enterMatch_(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitMatch_" ):
                listener.exitMatch_(self)




    def match_(self):

        localctx = TuringMachineParser.Match_Context(self, self._ctx, self.state)
        self.enterRule(localctx, 8, self.RULE_match_)
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 59
            self.match(TuringMachineParser.IDENTIFIER)
        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class ActionsContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def ACTIONS(self):
            return self.getToken(TuringMachineParser.ACTIONS, 0)

        def IDENTIFIER(self):
            return self.getToken(TuringMachineParser.IDENTIFIER, 0)

        def getRuleIndex(self):
            return TuringMachineParser.RULE_actions

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterActions" ):
                listener.enterActions(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitActions" ):
                listener.exitActions(self)




    def actions(self):

        localctx = TuringMachineParser.ActionsContext(self, self._ctx, self.state)
        self.enterRule(localctx, 10, self.RULE_actions)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 61
            _la = self._input.LA(1)
            if not(_la==TuringMachineParser.IDENTIFIER or _la==TuringMachineParser.ACTIONS):
                self._errHandler.recoverInline(self)
            else:
                self._errHandler.reportMatch(self)
                self.consume()
        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class State_defContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def IDENTIFIER(self):
            return self.getToken(TuringMachineParser.IDENTIFIER, 0)

        def OPAREN(self):
            return self.getToken(TuringMachineParser.OPAREN, 0)

        def symargs(self):
            return self.getTypedRuleContext(TuringMachineParser.SymargsContext,0)


        def CPAREN(self):
            return self.getToken(TuringMachineParser.CPAREN, 0)

        def getRuleIndex(self):
            return TuringMachineParser.RULE_state_def

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterState_def" ):
                listener.enterState_def(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitState_def" ):
                listener.exitState_def(self)




    def state_def(self):

        localctx = TuringMachineParser.State_defContext(self, self._ctx, self.state)
        self.enterRule(localctx, 12, self.RULE_state_def)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 63
            self.match(TuringMachineParser.IDENTIFIER)
            self.state = 68
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            if _la==TuringMachineParser.OPAREN:
                self.state = 64
                self.match(TuringMachineParser.OPAREN)
                self.state = 65
                self.symargs()
                self.state = 66
                self.match(TuringMachineParser.CPAREN)


        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class SymargsContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def IDENTIFIER(self, i:int=None):
            if i is None:
                return self.getTokens(TuringMachineParser.IDENTIFIER)
            else:
                return self.getToken(TuringMachineParser.IDENTIFIER, i)

        def COMMA(self, i:int=None):
            if i is None:
                return self.getTokens(TuringMachineParser.COMMA)
            else:
                return self.getToken(TuringMachineParser.COMMA, i)

        def getRuleIndex(self):
            return TuringMachineParser.RULE_symargs

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterSymargs" ):
                listener.enterSymargs(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitSymargs" ):
                listener.exitSymargs(self)




    def symargs(self):

        localctx = TuringMachineParser.SymargsContext(self, self._ctx, self.state)
        self.enterRule(localctx, 14, self.RULE_symargs)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 70
            self.match(TuringMachineParser.IDENTIFIER)
            self.state = 75
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            while _la==TuringMachineParser.COMMA:
                self.state = 71
                self.match(TuringMachineParser.COMMA)
                self.state = 72
                self.match(TuringMachineParser.IDENTIFIER)
                self.state = 77
                self._errHandler.sync(self)
                _la = self._input.LA(1)

        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class State_Context(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def state_name2(self):
            return self.getTypedRuleContext(TuringMachineParser.State_name2Context,0)


        def OPAREN(self):
            return self.getToken(TuringMachineParser.OPAREN, 0)

        def args(self):
            return self.getTypedRuleContext(TuringMachineParser.ArgsContext,0)


        def CPAREN(self):
            return self.getToken(TuringMachineParser.CPAREN, 0)

        def getRuleIndex(self):
            return TuringMachineParser.RULE_state_

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterState_" ):
                listener.enterState_(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitState_" ):
                listener.exitState_(self)




    def state_(self):

        localctx = TuringMachineParser.State_Context(self, self._ctx, self.state)
        self.enterRule(localctx, 16, self.RULE_state_)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 78
            self.state_name2()
            self.state = 83
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            if _la==TuringMachineParser.OPAREN:
                self.state = 79
                self.match(TuringMachineParser.OPAREN)
                self.state = 80
                self.args()
                self.state = 81
                self.match(TuringMachineParser.CPAREN)


        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class State_name2Context(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def state_name(self):
            return self.getTypedRuleContext(TuringMachineParser.State_nameContext,0)


        def getRuleIndex(self):
            return TuringMachineParser.RULE_state_name2

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterState_name2" ):
                listener.enterState_name2(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitState_name2" ):
                listener.exitState_name2(self)




    def state_name2(self):

        localctx = TuringMachineParser.State_name2Context(self, self._ctx, self.state)
        self.enterRule(localctx, 18, self.RULE_state_name2)
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 85
            self.state_name()
        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class State_nameContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def IDENTIFIER(self):
            return self.getToken(TuringMachineParser.IDENTIFIER, 0)

        def getRuleIndex(self):
            return TuringMachineParser.RULE_state_name

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterState_name" ):
                listener.enterState_name(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitState_name" ):
                listener.exitState_name(self)




    def state_name(self):

        localctx = TuringMachineParser.State_nameContext(self, self._ctx, self.state)
        self.enterRule(localctx, 20, self.RULE_state_name)
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 87
            self.match(TuringMachineParser.IDENTIFIER)
        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class ArgsContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def arg(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(TuringMachineParser.ArgContext)
            else:
                return self.getTypedRuleContext(TuringMachineParser.ArgContext,i)


        def COMMA(self, i:int=None):
            if i is None:
                return self.getTokens(TuringMachineParser.COMMA)
            else:
                return self.getToken(TuringMachineParser.COMMA, i)

        def getRuleIndex(self):
            return TuringMachineParser.RULE_args

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterArgs" ):
                listener.enterArgs(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitArgs" ):
                listener.exitArgs(self)




    def args(self):

        localctx = TuringMachineParser.ArgsContext(self, self._ctx, self.state)
        self.enterRule(localctx, 22, self.RULE_args)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 89
            self.arg()
            self.state = 94
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            while _la==TuringMachineParser.COMMA:
                self.state = 90
                self.match(TuringMachineParser.COMMA)
                self.state = 91
                self.arg()
                self.state = 96
                self._errHandler.sync(self)
                _la = self._input.LA(1)

        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class ArgContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def state_(self):
            return self.getTypedRuleContext(TuringMachineParser.State_Context,0)


        def lsymbol(self):
            return self.getTypedRuleContext(TuringMachineParser.LsymbolContext,0)


        def getRuleIndex(self):
            return TuringMachineParser.RULE_arg

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterArg" ):
                listener.enterArg(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitArg" ):
                listener.exitArg(self)




    def arg(self):

        localctx = TuringMachineParser.ArgContext(self, self._ctx, self.state)
        self.enterRule(localctx, 24, self.RULE_arg)
        try:
            self.state = 99
            self._errHandler.sync(self)
            la_ = self._interp.adaptivePredict(self._input,9,self._ctx)
            if la_ == 1:
                self.enterOuterAlt(localctx, 1)
                self.state = 97
                self.state_()
                pass

            elif la_ == 2:
                self.enterOuterAlt(localctx, 2)
                self.state = 98
                self.lsymbol()
                pass


        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx





