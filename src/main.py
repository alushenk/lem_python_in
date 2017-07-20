from tkinter import *
from app import App
from graph import Graph
from parse import *
import sys
from collections import deque


def find_shortest_path(graph):
    start = graph.start_room
    end = graph.end_room
    rooms = graph.rooms
    lines = graph.lines
    path = []
    while start != end and start not in path:
        path.append(start.name)
        start = start.connections[0]
    if start == end:
        path.append(start.name)
    return path


def main():
    root = Tk()
    app = App(root, 800, 650)
    graph = Graph()

    if len(sys.argv) == 3 and sys.argv[1] == '-s':
        with open(sys.argv[2], 'r') as file:
            source = file.readlines()
    else:
        source = sys.stdin.readlines()
    source = deque(source)
    parse_ants(graph, source.popleft().rstrip('\n'))
    parse_rooms(graph, source)
    parse_lines(graph, source)

    app.create_lines(graph)
    app.create_rooms(graph)

    # path = find_shortest_path(graph)
    # print(', '.join(path))

    app.canvas.pack()
    root.mainloop()


if __name__ == "__main__":
    main()
