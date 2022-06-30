import ADT

from functools import singledispatchmethod

class RemoveStar(object):
    def __init__(self, program):
        self.program = program

    @singledispatchmethod
    def remove_arg_star(self, arg: ADT.State, symbol: ADT.Symbol):
        if arg.name.name == ADT.SYMBOL_ANY:
            return self.remove_arg_star(ADT.Symbol(ADT.SYMBOL_ANY), symbol)

        return self.remove_state_star(arg, symbol)

    @remove_arg_star.register
    def _(self, arg: ADT.Symbol, symbol: ADT.Symbol):
        if arg.sym == ADT.SYMBOL_ANY:
            return symbol

        return arg

    @remove_arg_star.register
    def _(self, arg: str, symbol: ADT.Symbol):
        if arg == ADT.SYMBOL_ANY:
            return symbol

        return arg

    def remove_state_star(self, state, symbol: ADT.Symbol):
        new_args = []
        for arg in state.args:
            new_args.append(self.remove_arg_star(arg, symbol))

        new_state = ADT.State(state.name, new_args)
        return new_state

    def dfs(self, instr: ADT.Instruction):
        for branch in instr.branches.values():
            if branch.next.name.name != "accept":
                # otherwise symbolic state
                if branch.next.name in self.program.instructions:
                    nexti = self.program.instructions[branch.next.name]
                    if nexti not in self.visited:
                        self.visited.add(nexti)
                        self.dfs(nexti)

        allsyms = (self.program.alphabet.asSet() | { ADT.SYMBOL_EMPTY })
        explicit_syms = set(m.sym.sym for m in instr.branches if not m.any)
        symbols_left = allsyms - explicit_syms

        starbr = instr.branches.get(ADT.Match(any=True), None)
        for symbol in symbols_left:
            new_match = ADT.Match(ADT.Symbol(symbol))

            new_actions = []
            for action in starbr.actions:
                if type(action) == ADT.Print and action.sym == ADT.SYMBOL_ANY:
                    new_actions.append(ADT.Print(symbol))
                else:
                    new_actions.append(action)

            new_next = self.remove_state_star(starbr.next, symbol)
            newbr = ADT.InstrBody(new_match, new_actions, new_next)
            instr.branches[new_match] = newbr

        del instr.branches[ADT.Match(any=True)]

    def remove_star(self):
        start_name = ADT.StateName("start")

        start = self.program.instructions[start_name]
        self.visited = { start }
        self.dfs(start)
        for instr in list(self.program.instructions.values()):
            if instr not in self.visited:
                self.visited.add(instr)
                self.dfs(instr)
