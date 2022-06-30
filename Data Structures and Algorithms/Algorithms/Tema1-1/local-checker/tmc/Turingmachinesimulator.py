import ADT
import NormalizeActions
import ExpandMacros
import RemoveStar
import Rename
import ExplicitTuringMachine as ETM
from Visitor import Transformer
import string

class Turingmachinesimulator(object):
    def __init__(self, program: ADT.Program, name="tm"):
        self.program = program
        self.idx = 0
        self.name_map = {}
        self.name = name

    def format_machine(self, em):
        s = f"name: {self.name}\ninit: {em.start}\naccept: {em.accept}\n\n"

        def format_instr(tr):
            dir_dict = {"L": "<", "R": ">", "H": "-"}
            sym_dict = {"#": "_"}
            rsym = sym_dict.get(tr.sym, tr.sym)
            wsym = sym_dict.get(tr.wsym, tr.wsym)
            dir = dir_dict[tr.dir.value]
            return f"{tr.state},{rsym}\n{tr.next},{wsym},{dir}\n\n"

        for transition in em.transitions:
            s += format_instr(transition)

        return s

    def transform(self):
        self.program = ETM.simplify_program(self.program)
        em = ETM.from_program(self.program)
        s = self.format_machine(em)
        return s
