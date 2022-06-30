import ADT
import NormalizeActions
import ExpandMacros
import RemoveStar
import Rename
import ExplicitTuringMachine as ETM
from Visitor import Transformer
import string


class CheckerFormat(object):
    def __init__(self, program: ADT.Program, name="tm"):
        self.program = program
        self.idx = 0
        self.name_map = {}
        self.name = name

    def format_machine(self, em):
        alphabet_s = " ".join(str(c) for c in em.alphabet.asSet()) + " #"
        s = f"{alphabet_s}\n{em.start}\n{em.accept}\n"

        def format_instr(tr):
            dir = tr.dir.value
            return f"{tr.state} {tr.sym} {tr.next} {tr.wsym} {dir}\n"

        for transition in em.transitions:
            s += format_instr(transition)

        return s

    def transform(self):
        self.program = ETM.simplify_program(self.program)
        em = ETM.from_program(self.program)
        s = self.format_machine(em)
        return s
