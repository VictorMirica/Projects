#!/usr/bin/env python3
import sys
sys.path.append("tmc/")
sys.path.append("tmc/parser/")
sys.path.append("tmc/parser/libs")
from antlr4 import *
from TuringMachineLexer import TuringMachineLexer
from TuringMachineParser import TuringMachineParser
from Listener import *

from antlr4.tree.Trees import Trees

import Turingmachinesimulator as TMS
import CheckerFormat as CF


def parse_program(stream) -> ADT.Program:
    lexer = TuringMachineLexer(stream)
    tokens = CommonTokenStream(lexer)
    parser = TuringMachineParser(tokens)

    tree = parser.program()
    v = Listener()
    walker = ParseTreeWalker()
    walker.walk(v, tree)
    return v.program


def main(argv):
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <file> [tms|checker]", file=sys.stderr)
        sys.exit(1)

    inp = FileStream(sys.argv[1], encoding='utf-8')
    prog = parse_program(inp)
    if sys.argv[2] == "tms":
        t = TMS.Turingmachinesimulator(prog)
    else:
        t = CF.CheckerFormat(prog)

    print(t.transform())
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
