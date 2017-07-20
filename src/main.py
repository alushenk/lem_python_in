import sys
import tkinter_test
from app import App
from room import Room
from ant import Ant


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
        lines.append((a, b))


def display_rooms(rooms):
    for name, room in rooms.items():
        print(name + ': ' + ', '.join(room.connections) + '\n')


def display_lines(lines):
    for elem in lines:
        a, b = elem
        print(a + ' ' + b)


def main():
    rooms = {}
    lines = []
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
        if line.startswith("#"):
            continue
        line = line.rstrip('\n')
        print(line)
        add_line(rooms, lines, line)

    display_rooms(rooms)
    display_lines(lines)
    tkinter_test.graphic(rooms, lines)


if __name__ == "__main__":
    main()
