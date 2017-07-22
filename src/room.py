class Room(object):
    def __init__(self, name, x, y):
        self.name = name
        if not x.isdigit() and not y.isdigit():
            print('Error! coordinates must be integers')
            exit()
        self.x = int(x)
        self.y = int(y)
        self.oval = None
        self.number = None
        self.connections = []
        self.ants = []

    def add_connection(self, vertex):
        if vertex not in self.connections:
            self.connections.append(vertex)
        else:
            print('Error! connection already exists')
            exit()
