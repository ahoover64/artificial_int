import random

class Cup:
    def __init__(self, n, choice_range):
        if n > choice_range:
            self.options = range(1, choice_range + 1)
        else:
            self.options = range(1, n + 1)
        self.lose_case = False
        self.current = 0

    def will_lose(self):
        return self.lose_case

    def random_num(self):
        if len(self.options) == 0:
            print "Error: random_num function"
            return
        self.current = random.choice(self.options) #self.options[-1]
        return self.current

    def random_lost(self):
        if len(self.options) == 0:
            print "Error: random_lost function"
            return
        self.options.remove(self.current)
        self.lose_case = (len(self.options) == 0)

    def remove_others(self):
        self.options = []
        self.options.append(self.current)

    def __str__(self):
        return str(self.options)
