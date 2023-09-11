from copy import deepcopy
class GoodIfrit:
    def init( self, height, name, goodness ):
        self.height = height
        self.name = name
        self.goodness = goodness

    def change_goodness(self, value):
        self.goodness += value
        if self.goodness < 0:
            self.goodness = 0

    def add(self, other):
        new = deepcopy(self)
        new.height += other
        return new

    def call(self, arg):
        return arg * self.goodness // self.height

    def str(self):
        return f'Good Ifrit {self.name}, height {self.height}, goodness {self.goodness}'

    def lt(self, other):
        return (self.goodness, self.height, self.name) < (other.goodness, other.height, other.name)

    def eq(self, other):
        return not self < other and not other < self

    def ne(self, other):
        return not self == other

    def ge(self, other):
        return not self < other

    def gt(self, other):
        return other < self

    def le(self, other):
        return not self > other

gi = GoodIfrit(80, "Hazrul", 3)
gi.change_goodness(4)
print(gi)
gi1 = gi + 15
print(gi1)
print(gi(31))