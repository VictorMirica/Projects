import sys
sys.path.append("libs/")
import TuringMachineParser as TMP
import TuringMachineListener as TML
import ADT


class Listener(TML.TuringMachineListener):
    def __init__(self):
        super().__init__()
        self.alphabet = None
        self.stack = []
        self.instructions = {}
        self.program = None

    def exitProgram(self, ctx: TMP.TuringMachineParser.ProgramContext):
        # remove the ending semicolon from the alphabet
        alphabet = ADT.Alphabet(ctx.ALPHABET().getText()[:-1])
        self.program = ADT.Program(alphabet, self.instructions)

    def exitInstruction(self, ctx: TMP.TuringMachineParser.InstructionContext):
        # normalize all instructions to have a star branch
        star_match = ADT.Match(any=True)
        if star_match not in self.instruction.branches:
            args = None
            if type(self.instruction.header) == ADT.FuncStateDef:
                args = self.instruction.header.symargs

            next = ADT.State(self.instruction.header.name, args)
            self.instruction.branches[star_match] = ADT.InstrBody(star_match,
                    [ADT.Movement(ADT.Direction("H"))], next)

        name = self.instruction.header.name
        self.instructions[name] = self.instruction

    def exitState_name(self, ctx: TMP.TuringMachineParser.State_nameContext):
        self.state_name = ctx.getText()

    def enterState_def(self, ctx: TMP.TuringMachineParser.State_defContext):
        self.symargs = []

    def exitSymargs(self, ctx: TMP.TuringMachineParser.SymargsContext):
        self.symargs = ctx.getText().split(",")

    def exitState_def(self, ctx: TMP.TuringMachineParser.State_defContext):
        name = ADT.StateName(ctx.IDENTIFIER().getText(), len(self.symargs))
        d = ADT.StateDef(name) if not ctx.symargs() \
                               else ADT.FuncStateDef(name, self.symargs)
        self.instruction = ADT.Instruction(d)

    def exitState_name2(self, ctx: TMP.TuringMachineParser.State_name2Context):
        self.stack.append(ADT.State(ADT.StateName(ctx.getText())))

    def exitArg(self, ctx: TMP.TuringMachineParser.ArgContext):
        top = self.stack[-1]
        # top.args.append(ctx.getText())
        top.args.append(self.crt_arg)

    def exitState_(self, ctx: TMP.TuringMachineParser.State_Context):
        self.arg_state = self.stack.pop()
        self.arg_state.name.arity = len(self.arg_state.args)
        self.crt_arg = self.arg_state

    def exitLsymbol(self, ctx: TMP.TuringMachineParser.LsymbolContext):
        self.crt_arg = ctx.getText()

    def enterInstr_body(self, ctx: TMP.TuringMachineParser.Instr_bodyContext):
        self.actions = []
        self.match_ = ADT.Match(any=True)

    def exitMatch_(self, ctx: TMP.TuringMachineParser.Match_Context):
        msym = ctx.IDENTIFIER().getText()
        assert len(msym) == 1, f"Match {msym} is not a single symbol!"
        if msym == ADT.SYMBOL_ANY:
            self.match_ = ADT.Match(any=True)
        else:
            self.match_ = ADT.Match(ADT.Symbol(msym))

    def exitActions(self, ctx: TMP.TuringMachineParser.ActionsContext):
        def parse_actions(s):
            def parse_action(a):
                sancheck = (a[0] == "P" and len(a) == 2) or (len(a) == 1)
                assert sancheck, f"Unknown action {a}!"
                if a[0] in "LRH":
                    return ADT.Movement(ADT.Direction(a))

                sym = ADT.SYMBOL_EMPTY if a[0] == "E" else a[1]
                return ADT.Print(sym)

            return [parse_action(a) for a in s.split(",")] if s else []

        self.actions = parse_actions(ctx.getText())

    def exitInstr_body(self, ctx: TMP.TuringMachineParser.Instr_bodyContext):
        instr_body = ADT.InstrBody(self.match_, self.actions, self.arg_state)
        self.instruction.branches[self.match_] = instr_body
