class Room(object):
    def __init__(self, name, x, y):
        if name.startswith('#') or name.startswith('L'):
            print('Error! wrong name')
            exit()
        self.name = name
        if not x.isdigit() and not y.isdigit():
            print('Error! coordinates must be integers')
            exit()
        self.x = int(x)
        self.y = int(y)
        self.oval = None
        self.number = None
        self.connections = []
        self.ant = 0

    def add_connection(self, vertex):
        if vertex not in self.connections:
            self.connections.append(vertex)
        else:
            print('Error! connection already exists')
            exit()

    def add_ant(self, ant):
        self.ant = ant

    def pop_ant(self):
        ant = self.ant
        self.ant = 0
        return ant

    def is_free(self):
        if self.ant == 0:
            return True
        else:
            return False

    def __str__(self):
        return self.name
