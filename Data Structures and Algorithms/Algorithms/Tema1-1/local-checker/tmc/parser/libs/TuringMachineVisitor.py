# Generated from TuringMachine.g4 by ANTLR 4.9.2
from antlr4 import *
if __name__ is not None and "." in __name__:
    from .TuringMachineParser import TuringMachineParser
else:
    from TuringMachineParser import TuringMachineParser

# This class defines a complete generic visitor for a parse tree produced by TuringMachineParser.

class TuringMachineVisitor(ParseTreeVisitor):

    # Visit a parse tree produced by TuringMachineParser#program.
    def visitProgram(self, ctx:TuringMachineParser.ProgramContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by TuringMachineParser#alphabet.
    def visitAlphabet(self, ctx:TuringMachineParser.AlphabetContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by TuringMachineParser#line.
    def visitLine(self, ctx:TuringMachineParser.LineContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by TuringMachineParser#comment.
    def visitComment(self, ctx:TuringMachineParser.CommentContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by TuringMachineParser#instruction.
    def visitInstruction(self, ctx:TuringMachineParser.InstructionContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by TuringMachineParser#instr_header.
    def visitInstr_header(self, ctx:TuringMachineParser.Instr_headerContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by TuringMachineParser#instr_body.
    def visitInstr_body(self, ctx:TuringMachineParser.Instr_bodyContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by TuringMachineParser#symbol_match.
    def visitSymbol_match(self, ctx:TuringMachineParser.Symbol_matchContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by TuringMachineParser#actions.
    def visitActions(self, ctx:TuringMachineParser.ActionsContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by TuringMachineParser#action.
    def visitAction(self, ctx:TuringMachineParser.ActionContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by TuringMachineParser#print_.
    def visitPrint_(self, ctx:TuringMachineParser.Print_Context):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by TuringMachineParser#erase.
    def visitErase(self, ctx:TuringMachineParser.EraseContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by TuringMachineParser#move.
    def visitMove(self, ctx:TuringMachineParser.MoveContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by TuringMachineParser#state_def.
    def visitState_def(self, ctx:TuringMachineParser.State_defContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by TuringMachineParser#state_template.
    def visitState_template(self, ctx:TuringMachineParser.State_templateContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by TuringMachineParser#symargs.
    def visitSymargs(self, ctx:TuringMachineParser.SymargsContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by TuringMachineParser#symarg.
    def visitSymarg(self, ctx:TuringMachineParser.SymargContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by TuringMachineParser#state.
    def visitState(self, ctx:TuringMachineParser.StateContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by TuringMachineParser#state_func.
    def visitState_func(self, ctx:TuringMachineParser.State_funcContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by TuringMachineParser#args.
    def visitArgs(self, ctx:TuringMachineParser.ArgsContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by TuringMachineParser#arg.
    def visitArg(self, ctx:TuringMachineParser.ArgContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by TuringMachineParser#concrete_state.
    def visitConcrete_state(self, ctx:TuringMachineParser.Concrete_stateContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by TuringMachineParser#symbol.
    def visitSymbol(self, ctx:TuringMachineParser.SymbolContext):
        return self.visitChildren(ctx)



del TuringMachineParser