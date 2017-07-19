#!../bin/python3

import sys
import time


class Room(object):
    def __init__(self, name, x, y):
        self.name = name
        if not x.isdigit() and not y.isdigit():
            print('Error! coordinates must be integers')
            exit()
        self.x = x
        self.y = y
        self.connections = []

    def add_connection(self, vertex):
        if vertex not in self.connections:
            self.connections.append(vertex)
        else:
            print('Error! connection already exists')
            exit()


def add_room(rooms, line):
    name, x, y = line.split(" ", 3)
    room = Room(name, x, y)
    rooms[name] = room
    return name


def add_line(rooms, lines, line):
    a, b = line.split("-", 2)
    if a in rooms and b in rooms:
        rooms[a].add_connection(b)
        rooms[b].add_connection(a)
        lines.add((a, b))


def display_rooms(rooms):
    for name, room in rooms.items():
        print(name + ': ' + ', '.join(room.connections) + '\n')


def main():
    rooms = {}
    lines = set()
    startroom = 0
    endroom = 0

    # time.sleep(10)
    number_of_ants = sys.stdin.readline().rstrip('\n')
    if not number_of_ants.isdigit():
        print('Error! parameter not a digit')
        exit()

    for line in sys.stdin:
        line = line.rstrip('\n')
        print(line)
        if line == '##start':
            line = sys.stdin.readline().rstrip('\n')
            print(line)
            startroom = add_room(rooms, line)
            continue
        if line == '##end':
            line = sys.stdin.readline().rstrip('\n')
            print(line)
            endroom = add_room(rooms, line)
            break
        if line.startswith("#"):
            continue
        add_room(rooms, line)

    for line in sys.stdin:
        line = line.rstrip('\n')
        print(line)
        add_line(rooms, lines, line)

    display_rooms(rooms)


if __name__ == "__main__":
    main()
