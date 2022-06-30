import ADT


class Rename(object):
    def __init__(self, program: ADT.Program):
        self.program = program
        self.idx = 0
        self.name_map = {}

    def get_new_name(self, old_name: ADT.StateName):
        if old_name.name in {"start", "accept"}:
            return old_name

        if old_name not in self.name_map:
            res = self.idx
            self.idx += 1
            self.name_map[old_name] = f"q{res}"

        return self.name_map[old_name]

    def rename(self):
        new_instrs = {}
        for instr in self.program.instructions.values():
            name = instr.header.name
            state_name = ADT.StateName(self.get_new_name(name))
            instr.header = ADT.StateDef(state_name)
            for body in instr.branches.values():
                name = body.next.name
                body.next = ADT.State(ADT.StateName(self.get_new_name(name)))

            new_instrs[state_name] = instr

        self.program.instructions = new_instrs
