class Ant(object):
    def __init__(self, name, x, y):
        self.name = name
        self.x = int(x)
        self.y = int(y)
        self.oval = None
        self.number = None

    def __str__(self):
        return self.name
