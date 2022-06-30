import ADT
from typing import overload
from Node import Node

from Visitor import Transformer

from functools import singledispatchmethod

class ExpandMacros(object):
    def __init__(self, program):
        self.program = program

    @singledispatchmethod
    def get_concrete_name(self, sym: ADT.Symbol) -> str:
        return sym.sym

    @get_concrete_name.register
    def _(self, s: str) -> str:
        return s

    @get_concrete_name.register
    def _(self, state: ADT.State) -> str:
        if state.args:
            args_s = "(" + ",".join(str(self.get_concrete_name(arg)) for arg in state.args) + ")"
        else:
            args_s = ""

        name_s = f"{state.name.name}{args_s}"
        return name_s


    def replace_state(self, state, rd) -> ADT.InstrBody:
        aux = rd.get(state.name.name, state.name.name)
        if type(aux) == ADT.State:
            aux = aux.name.name

        new_name = ADT.StateName(aux, state.name.arity)

        new_args = []
        for arg in state.args:
            if type(arg) == ADT.State:
                new_arg = self.replace_state(arg, rd)
            elif type(arg) == ADT.Symbol:
                new_arg = rd.get(arg.sym, arg.sym)
            elif type(arg) == str:
                new_arg = rd.get(arg, arg)

            new_args.append(new_arg)

        return ADT.State(new_name, new_args)


    def replace(self, ib: ADT.InstrBody, rd) -> ADT.InstrBody:
        if not ib.match.any:
            aux = rd.get(ib.match.sym, ib.match.sym)
            if type(aux) == ADT.State and len(aux.name.name) == 1:
                aux = ADT.Symbol(aux.name.name)

            new_match = ADT.Match(aux)
        else:
            new_match = ib.match

        new_actions = []
        for action in ib.actions:
            if type(action) == ADT.Print:
                new_action = ADT.Print(rd.get(action.sym, action.sym))
            elif type(action) == ADT.Movement:
                new_action = ADT.Movement(ADT.Direction(rd.get(action.direction.value, action.direction.value)))
            else:
                new_action = action

            new_actions.append(new_action)

        new_state = self.replace_state(ib.next, rd)
        return ADT.InstrBody(new_match, new_actions, new_state)


    def instantiate(self, name: ADT.StateName, state: ADT.State,
                    template: ADT.Instruction) -> ADT.Instruction:
        new_instr = ADT.Instruction(ADT.StateDef(name))
        for m, ib in template.branches.items():
            rd = {sa: ca for sa, ca in zip(template.header.symargs, state.args)}
            new_branch = self.replace(ib, rd)
            new_instr.branches[new_branch.match] = new_branch

        return new_instr

    @singledispatchmethod
    def concretize_arg(self, sym: ADT.Symbol):
        return sym

    @concretize_arg.register
    def _(self, s: str):
        return s

    @concretize_arg.register
    def _(self, state: ADT.State):
        if state.name.name == ADT.SYMBOL_ANY:
            return self.concretize_arg(ADT.Symbol(ADT.SYMBOL_ANY))

        return self.concretize_state(state)

    def concretize_state(self, state: ADT.State):
        if not state.args:
            return state

        state.args = [self.concretize_arg(arg) for arg in state.args]
        concrete_name = ADT.StateName(self.get_concrete_name(state))
        if concrete_name not in self.program.instructions:
            concrete = self.instantiate(concrete_name, state, self.program.instructions[state.name])
            self.program.instructions[concrete_name] = concrete

        return ADT.State(concrete_name)

    def dfs(self, instr: ADT.Instruction):
        for branch in instr.branches.values():
            if branch.next.args:
                branch.next = self.concretize_state(branch.next)

            if branch.next.name.name != "accept":
                nexti = self.program.instructions[branch.next.name]
                if nexti not in self.visited:
                    self.visited.add(nexti)
                    self.dfs(nexti)

    def expand_macros(self):
        start_name = ADT.StateName("start")
        start = self.program.instructions[start_name]
        self.visited = { start }
        self.dfs(start)
        for instr in list(self.program.instructions.values()):
            if instr not in self.visited \
                    and type(instr.header) != ADT.FuncStateDef:
                self.visited.add(instr)
                self.dfs(instr)

    def remove_macros(self):
        new_instrs = {}
        for name, instr in self.program.instructions.items():
            if type(instr.header) != ADT.FuncStateDef:
                new_instrs[name] = instr

        self.program.instructions = new_instrs
