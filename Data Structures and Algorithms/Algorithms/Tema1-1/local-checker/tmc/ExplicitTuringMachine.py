import ADT

import RemoveStar
import ExpandMacros
import NormalizeActions
import Rename


class Transition(object):
    state: str = None
    sym: ADT.Symbol = None
    next: str = None
    wsym: ADT.Symbol = None
    dir: ADT.Direction = None

    def __init__(self, state, sym, next, wsym, dir):
        self.state = state
        self.sym = sym
        self.next = next
        self.wsym = wsym
        self.dir = dir


class TuringMachine(object):
    alphabet = None
    start = None
    accept = None
    transitions: list[Transition]

    def __init__(self, start, accept, transitions, alphabet=None):
        self.start = start
        self.accept = accept
        self.transitions = transitions
        self.alphabet = alphabet


def simplify_program(program):
    rs = RemoveStar.RemoveStar(program)
    rs.remove_star()

    ex = ExpandMacros.ExpandMacros(program)
    ex.expand_macros()
    ex.remove_macros()

    nm = NormalizeActions.NormalizeActions(program)
    nm.normalize_actions()

    rn = Rename.Rename(program)
    rn.rename()

    return program


def from_program(program):
    def convert(name, instr):
        state = name
        sym = instr.match.sym
        next = instr.next.name.name
        wsym = instr.actions[0].sym
        dir = instr.actions[1].direction
        return Transition(state, sym, next, wsym, dir)

    transitions = []
    for name, instruction in program.instructions.items():
        for instr in instruction.branches.values():
            transitions.append(convert(name.name, instr))

    return TuringMachine("start", "accept", transitions, program.alphabet)
