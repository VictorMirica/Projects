import ADT
import random


class NormalizeActions(object):
    def __init__(self, program):
        self.program = program
        random.seed(1)

    def dfs(self, instr: ADT.Instruction):
        for branch in instr.branches.values():
            def split_actions(symbol: ADT.Symbol, actions: list[ADT.Action]):
                if len(actions) == 0:
                    new_actions = [ADT.Print(symbol), ADT.Movement(ADT.Direction("H"))]
                    next_actions = []
                elif len(actions) == 1:
                    if type(actions[0]) == ADT.Print:
                        new_actions = [actions[0], ADT.Movement(ADT.Direction("H"))]
                        next_actions = []
                    else:
                        new_actions = [ADT.Print(symbol), actions[0]]
                        next_actions = []
                elif type(actions[0]) == ADT.Print:
                    if type(actions[1]) == ADT.Print:
                        new_actions, next_actions = split_actions(actions[1:])
                    else:
                        new_actions = actions[:2]
                        next_actions = actions[2:]
                else:
                    new_actions = [ADT.Print(symbol), actions[0]]
                    next_actions = actions[1:]

                return new_actions, next_actions

            def gen_new_state_name():
                idx = random.randint(100000, 999999)
                name = ADT.StateName(f"q{idx}")
                while name in self.program.instructions:
                    idx = random.randint(100000, 999999)
                    name = ADT.StateName(f"q{idx}")

                return name

            symbol = branch.match.sym
            if symbol is None:
                symbol = ADT.SYMBOL_ANY

            new_actions, next_actions = split_actions(symbol, branch.actions)
            branch.actions = new_actions
            if next_actions:
                new_name = gen_new_state_name()
                new_header = ADT.StateDef(new_name)
                any = ADT.Match(any=True)
                new_body = ADT.InstrBody(any, next_actions, branch.next)
                branch.next = ADT.State(new_name)
                self.program.instructions[new_name] = ADT.Instruction(new_header,
                        {any: new_body})


            if branch.next.name.name != "accept":
                nexti = self.program.instructions[branch.next.name]
                if nexti not in self.visited:
                    self.visited.add(nexti)
                    self.dfs(nexti)


    def normalize_actions(self):
        start_name = ADT.StateName("start")
        start = self.program.instructions[start_name]
        self.visited = { start }
        self.dfs(start)

        for instr in list(self.program.instructions.values()):
            if instr not in self.visited \
                    and type(instr.header) != ADT.FuncStateDef:
                self.visited.add(instr)
                self.dfs(instr)
