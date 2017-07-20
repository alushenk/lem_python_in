import sys
from room import Room


class Graph(object):
    def __init__(self):
        self.rooms = {}
        self.lines = []
        self.start_room = 0
        self.end_room = 0

    def add_room(self, name, x, y):
        room = Room(name, x, y)
        self.rooms[name] = room
        return room

    def add_start(self, name, x, y):
        self.start_room = self.add_room(name, x, y)

    def add_end(self, name, x, y):
        self.end_room = self.add_room(name, x, y)

    def add_line(self, a, b):
        if a in self.rooms and b in self.rooms:
            self.rooms[a].add_connection(b)
            self.rooms[b].add_connection(a)
            self.lines.append((a, b))
        else:
            print('Error! linking non-existent rooms')
            sys.exit()

    def print_rooms(self):
        for name, room in self.rooms.items():
            print(name + ': ' + ', '.join(room.connections) + '\n')

    def print_lines(self):
        for elem in self.lines:
            a, b = elem
            print('{0} {1}'.format(a, b))
