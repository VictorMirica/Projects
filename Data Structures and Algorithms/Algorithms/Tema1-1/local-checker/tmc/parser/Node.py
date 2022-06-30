from __future__ import annotations

from abc import ABC, abstractmethod
from functools import singledispatchmethod


class SourceInfo:
    def __init__(self, line: int, count: int):
        assert(line > 0 and count > 0)
        self.line = line
        self.count = line


class Node(ABC):
    def __init__(self, srcInfo: SourceInfo = None):
        self.children = []
        self.srcInfo = srcInfo

    def visit_preorder(self, v):
        v(self)

    def visit_postorder(self, v):
        v(self)

    def transform_preorder(self, v):
        return v(self)

    def transform_postorder(self, v):
        return v(self)
