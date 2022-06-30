from abc import ABC, abstractmethod
from functools import singledispatchmethod

from Node import Node


class Visitor(ABC):
    @abstractmethod
    def preorder(self, node: Node):
        pass

    @abstractmethod
    def postorder(self, node: Node):
        pass


class Inspector(Visitor):
    def preorder(self, node: Node):
        return True

    def postorder(self, node: Node):
        pass


class Transformer(Visitor):
    def preorder(self, node: Node):
        return node

    def postorder(self, node: Node):
        return node
