#!/usr/bin/env python3

import sys
sys.path.append("tmc/")
sys.path.append("tmc/parser")
sys.path.append("tmc/parser/libs")
from antlr4 import *
import filecmp
from os.path import exists

import CheckerFormat as CF
import ParseMain

stepLimit = 7096

def step(config, tranzitii):
    if (config[1], config[2][0]) in tranzitii.keys():
        change = tranzitii[(config[1], config[2][0])]
        if change[2] == "R":
            config = (config[0] + change[1], change[0], config[2][1:])
        if change[2] == "L":
            config = (config[0][:-1], change[0], config[0]
                        [-1]+change[1]+config[2][1:])
        if change[2] == "H":
            config = (config[0], change[0], change[1]+config[2][1:])
        if config[0] == "":
            config = ("#", config[1], config[2])
        if config[2] == "":
            config = (config[0], config[1], "#")
        return (True, config)
    return (False, config)


def accept(w, turing):
    config = ("#", turing[1], w)
    tm = turing[3]  # tranzitii
    sf = turing[2]  # stari finale
    stepCount = 0
    while True and stepCount < stepLimit:
        stepCount += 1
        (val, config) = step(config, tm)
        if val == False:
            result = config[0] + config[2] # ce e scris pe banda la final
            result = result.lstrip("#")
            result = result.rstrip("#")
            if config[1] in sf:
                return (True, result)
            return (False, result)
    raise ValueError("Exceeded maximum number of steps. Fix your code!")


def readTM(fd_in):
    alfabet = fd_in.readline().split()
    I = fd_in.readline().rstrip('\n') # starea initiala
    F = fd_in.readline().split() # citire stari finale
    if F[0] == "-":
        F = []
    # citire tranzitii
    delta = {}
    transitions = fd_in.readlines()
    for line in transitions:
        if line != "\n":
            arr = line.split()
            delta.update({(arr[0], arr[1]): (arr[2], arr[3], arr[4])})
    # creare masina turing
    turing_machine = (alfabet, I, F, delta)
    return turing_machine


def checkTest(infile, outfile, specfile):
    fin = open(infile, "r")
    word = fin.readline() 
    fin.close()

    mt_fd = open(specfile, "r")
    turing_machine = readTM(mt_fd)
    mt_fd.close()

    rez = accept(word, turing_machine)
    fout = open(outfile, "w")
    fout.write(rez[1])
    fout.close()


def getTestPath(taskset, task, test, ext):
    return f"tests/task_{taskset}_{task}/test{test}.{ext}"

def getSolutionPath(taskset, task, ext):
    return f"../solutions/task_{taskset}_{task}.{ext}"

def getExceptionMessage(taskset, task, test):
    return f"{taskset}.{task}/{test}"


def compileSolution(taskset, task):
    tmfile = getSolutionPath(taskset, task, "tm") # to get relative path to student's solution
    specfile = getSolutionPath(taskset, task, "spec")

    inp = FileStream(tmfile, encoding="utf-8")
    prog = ParseMain.parse_program(inp)
    t = CF.CheckerFormat(prog)
    with open(specfile, "w") as fout:
        s = t.transform()
        fout.write(s)

    return specfile

def showHelp():
    print("""
    Usage:
    ./tester.py (or python3 tester.py) help - show this message
    ./tester.py (or ./tester.py all) - run all tests
    ./tester.py 1 - run taskset 1
    ./tester.py 1 1 - run taskset 1, task 1
    ./tester.py 1 1 1 - run taskset 1, task 1, test 1
    """)

def run(taskset, task, test, exceptions):
    inPath = getTestPath(taskset, task, test, "in")
    outPath = getTestPath(taskset, task, test, "out")
    refPath = getTestPath(taskset, task, test, "ref")
    
    outEqRef = False
    try:
        solPath = compileSolution(taskset, task) #uncomment after implementing compileSolution
        checkTest(inPath, outPath, solPath) #uncomment after implementing compileSolution
        outEqRef = filecmp.cmp(outPath, refPath, False)
    except Exception as e:
        raise e
        exceptions.append(e)

    testScoreMax = 1
    if (taskset == "1" and task == "4") or (taskset == "2" and task == "3"):
        testScoreMax = 7
    if (taskset == "2" and task == "2"):
        testScoreMax = 2

    if outEqRef:
        return (testScoreMax, testScoreMax)
    else:
        return (0, testScoreMax)

def runFromArgs():
    nargs = len(sys.argv)
    args = sys.argv

    (st, mt) = (0, 0)
    exceptions = []

    if nargs == 4:
        (st, mt) = run(args[1], args[2], args[3], exceptions)
        print(f"Task {args[1]}.{args[2]} test {args[3]}              {st}/{mt}")

    if nargs == 3:
        for test in "12345":
            (s, m) = run(args[1], args[2], test, exceptions)
            print(f"Task {args[1]}.{args[2]} test {test}              {s}/{m}")
            st = st + s
            mt = mt + m

    if nargs == 2 and args[1] == "1":
        for task in "1234":
            (stt, mtt) = (0, 0)
            for test in "12345":
                (s, m) = run(args[1], task, test, exceptions)
                stt = stt + s
                mtt = mtt + m
            print(f"Task {args[1]}.{task}                     {stt}/{mtt}")
            st = st + stt
            mt = mt + mtt

    if nargs == 2 and args[1] == "2":
        for task in "123":
            (stt, mtt) = (0, 0)
            for test in "12345":
                (s, m) = run(args[1], task, test, exceptions)
                stt = stt + s
                mtt = mtt + m
            print(f"Task {args[1]}.{task}                     {stt}/{mtt}")
            st = st + stt
            mt = mt + mtt

    if nargs == 1 or (nargs == 2 and args[1] == "all"):
        for task in "1234":
            (stt, mtt) = (0, 0)
            for test in "12345":
                (s, m) = run("1", task, test, exceptions)
                stt = stt + s
                mtt = mtt + m
            print(f"Task 1.{task}                     {stt}/{mtt}")
            st = st + stt
            mt = mt + mtt

        for task in "123":
            (stt, mtt) = (0, 0)
            for test in "12345":
                (s, m) = run("2", task, test, exceptions)
                stt = stt + s
                mtt = mtt + m
            print(f"Task 2.{task}                     {stt}/{mtt}")
            st = st + stt
            mt = mt + mtt

    return (st, mt, exceptions)

if __name__ == "__main__":
    if len(sys.argv) == 2 and sys.argv[1] == "help":
        showHelp()
    else:
        print("\n---------- AA: Tema 1 ----------\n")
        (score, scoreMax, exceptions) = runFromArgs()
        print("\n--------------------------------\n")
    if len(exceptions) > 0:
        exceptionsStr = '\n' + '\n'.join(str(x) for x in exceptions) + '\n'
        print(f"Errors:{exceptionsStr}")

    if exists("../README"):
        print(f"Total: {score}/{scoreMax}\n")
    else:
        print(f"No README.. no points!\n")
