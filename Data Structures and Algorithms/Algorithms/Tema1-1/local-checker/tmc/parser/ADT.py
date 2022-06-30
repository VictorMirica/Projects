from __future__ import annotations
from enum import Enum
from abc import ABC
from typing import Optional, Union
import string

from Node import Node

SYMBOL_ANY = "*"
SYMBOL_EMPTY = "#"

class Symbol(Node):
    sym: str

    def __init__(self, sym):
        assert (len(sym) == 1), "A symbol must be exactly one character!"
        self.sym = sym

    def __eq__(self, other):
        if type(other) == Symbol:
            return self.sym == other.sym
        elif type(other) == str:
            return self.sym == other
        return False

    def __hash__(self):
        return hash(self.sym)

    def __str__(self):
        return self.sym


class Symarg(Symbol):
    VALID_SYMARGS = string.ascii_letters

    def __init__(self, sym):
        assert (sym[0] in VALID_SYMARGS), "Invalid symarg!"
        super().__init__()


class Alphabet(Node):
    alphabet: dict[Symbol, None]

    def __init__(self, symbols):
        self.alphabet = dict.fromkeys(symbols)

    def asSet(self):
        return set(self.alphabet.keys())

    def __str__(self):
        return "".join(self.alphabet)

    def transform_postorder(self, v):
        return v(Alphabet(self.alphabet))


class Action(ABC):
    pass


class Direction(Enum):
    LEFT = "L"
    RIGHT = "R"
    HOLD = "H"

    def __str__(self):
        return f"{self.value}"


class Movement(Action):
    direction: Direction

    def __init__(self, direction: Direction):
        self.direction = direction

    def __str__(self):
        return f"{self.direction}"

    def transform_postorder(self, v):
        new_dir = self.direction.transform_postorder(v)
        return v(Movement(new_dir))


class Print(Action):
    sym: Symbol

    def __init__(self, sym: Symbol):
        self.sym = sym

    def __str__(self):
        return f"P{self.sym}"

    def transform_postorder(self, v):
        new_sym = self.sym.transform_postorder(v)
        return v(Print(new_sym))


class StateName(Node):
    name: str
    arity: int

    def __init__(self, name: str, arity: int = 0):
        self.name = name
        self.arity = arity

    def __eq__(self, other):
        return self.name == other.name and self.arity == other.arity

    def __hash__(self):
        return hash((self.name, self.arity))

    def __str__(self):
        return self.name

    def transform_postorder(self, v):
        new_name = self.name.transform_postorder(v)
        new_args = []
        for arg in self.args:
            new_args.append(arg.transform_postorder(v))

        return v(State(new_name, new_args))


Argument = Union["State", Symbol, str]

class State(Node):
    name: StateName
    args: list[Argument]

    def __init__(self, name=None, args=None):
        self.name = name
        self.args = [] if args is None else args

    def __str__(self):
        args_s = ("(" + ", ".join(str(a) for a in self.args) + ")") if self.args else ""
        return f"{self.name}{args_s}"

    def visit_preorder(self, v):
        v(self)
        self.name.visit_preorder(v)
        for arg in self.args:
            arg.visit_preorder(v)

    def visit_postorder(self, v):
        self.name.visit_preorder(v)
        for arg in self.args:
            arg.visit_preorder(v)

        v(self)

    def transform_preorder(self, v):
        res = v(self)
        res.name = v(self.name)
        res.args = []
        return res

    def transform_postorder(self, v):
        new_name = self.name.transform_postorder(v)
        new_args = []
        for arg in self.args:
            new_args.append(arg.transform_postorder(v))

        return v(State(new_name, new_args))


class Match(Node):
    sym: Symbol
    any: bool

    def __init__(self, sym=None, any: bool=False):
        assert (sym is not None) != any, \
            "A match must be either 'any' or a particular symbol!"

        self.sym = sym
        self.any = any

    def __eq__(self, other):
        return self.sym == other.sym or (self.any and other.any)

    def __hash__(self):
        if self.any:
            return hash(self.any)

        return hash(self.sym)

    def __str__(self):
        return SYMBOL_ANY if self.any else str(self.sym)

    def visit_preorder(self, v):
        v(self)
        self.sym.visit_preorder(v)

    def visit_postorder(self, v):
        self.sym.visit_preorder(v)
        v(self)

    def transform_preorder(self, v):
        res = v(self)
        res.sym = v(self.sym)
        return res

    def transform_postorder(self, v):
        if self.sym is not None:
            new_sym = self.sym.transform_postorder(v)
            return v(Match(sym=new_sym))
        else:
            return v(Match(any=True))


class InstrBody(Node):
    match: Match
    actions: list[Action]
    next: State

    def __init__(self, match=None, actions=None, next=None):
        self.match = match
        self.actions = actions
        self.next = next

    def __str__(self):
        actions_str = ",".join(str(a) for a in self.actions) if self.actions else ""
        return f"{self.match} {actions_str} {self.next}"

    def visit_preorder(self, v):
        pass

    def visit_postorder(self, v):
        pass

    def transform_preorder(self, v):
        pass

    def transform_postorder(self, v):
        new_match = self.match.transform_postorder(v)
        new_actions = []
        for action in self.actions:
            new_actions.append(action.transform_postorder(v))

        new_next = self.next.transform_postorder(v)
        return v(InstrBody(new_match, new_actions, new_next))


class StateDef(Node):
    name: StateName

    def __init__(self, name=None):
        self.name = name

    def __str__(self):
        return str(self.name)

    def visit_preorder(self, v):
        v(self)
        self.name.visit_preorder(v)

    def visit_postorder(self, v):
        self.name.visit_preorder(v)
        v(self)

    def transform_preorder(self, v):
        res = v(self)
        res.name = self.name.transform_preorder(v)
        return res

    def transform_postorder(self, v):
        pass


class FuncStateDef(StateDef):
    symargs: list[Symarg]

    def __init__(self, name: StateName, symargs=None):
        super().__init__(name)
        self.symargs = symargs

    def __str__(self):
        symargs_s = "" if not self.symargs \
                       else "(" + ", ".join(map(str, self.symargs)) + ")"
        return f"{self.name}{symargs_s}"

    def visit_preorder(self, v):
        v(self)
        self.name.visit_preorder(v)
        for arg in self.symargs:
            arg.visit_preorder(v)

    def visit_postorder(self, v):
        self.name.visit_preorder(v)
        for arg in self.symargs:
            arg.visit_preorder(v)

        v(self)

    def transform_preorder(self, v):
        res = v(self)
        res.name = self.name.transform_preorder(v)
        res.symargs = [a.transform_preorder(v) for a in self.symargs]
        return res

    def transform_postorder(self, v):
        new_name = self.name.transform_preorder(v)
        new_symargs = [a.transform_postorder(v) for a in self.symargs]
        return v(FuncState(new_name, new_symargs))


class Instruction(Node):
    header: StateDef
    branches: dict[Match, InstrBody]

    def __init__(self, header: StateDef, branches: dict[Match, InstrBody] = None):
        self.header = header
        self.branches = {} if branches is None else branches

    def __str__(self):
        body_s = "\n\t".join(str(v) for v in self.branches.values())
        return f"{self.header} {body_s}"

    def visit_preorder(self, v):
        v(self)
        self.header.visit_preorder(v)
        for branch in self.branches.values():
            branch.visit_preorder(v)

    def visit_postorder(self, v):
        self.header.visit_preorder(v)
        for branch in self.branches.values():
            branch.visit_preorder(v)

        v(self)

    def transform_preorder(self, v):
        res = v(self)

        res.header = self.header.transform_preorder(v)
        new_branches = {}
        for branch in self.branches.values():
            new_branch = branch.transform_preorder(v)
            new_branches[new_branch.match] = new_branch

        res.branches = new_branches
        return res

    def transform_postorder(self, v):
        new_header = self.header.transform_postorder(v)
        new_branches = {}
        for branch in self.branches.values():
            new_branch = branch.transform_postorder(v)
            new_branches[new_branch.match] = new_branch

        return v(Instruction(new_header, new_branches))


class Program(Node):
    alphabet: Alphabet
    instructions: dict[StateName, Instruction]

    def __init__(self, alphabet, instructions: dict[str, Instruction] = None):
        self.alphabet = alphabet
        self.instructions = {} if instructions is None else instructions

    def __str__(self):
        instr_s = "\n\n".join(map(str, self.instructions.values()))
        return f"{self.alphabet};\n\n{instr_s}"

    def visit_preorder(self, v):
        v(self)
        self.alphabet.visit_preorder(v)
        for instruction in self.instructions.values():
            instruction.visit_preorder(v)

    def visit_postorder(self, v):
        self.alphabet.visit_postorder(v)
        for instruction in self.instructions.values():
            instruction.visit_postorder(v)

        v(self)

    def transform_preorder(self, v):
        res = v(self)

        res.alphabet = self.alphabet.transform_preorder(v)
        res.instructions = {}
        for instruction in self.instructions.values():
            new_instruction = instruction.transform_preorder(v)
            res.instructions[new_instruction.name] = new_instruction

        return res

    def transform_postorder(self, v):
        new_alphabet = self.alphabet.transform_postorder(v)
        new_instructions = {}
        for instruction in self.instructions.values():
            new_instruction = instruction.transform_postorder(v)
            new_instructions[new_instruction.name] = new_instruction

        return v(Program(new_alphabet, new_instructions))
