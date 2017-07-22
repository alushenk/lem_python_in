from tkinter import *
from app import App
from graph import Graph
from parse import *
import sys
from collections import deque
import time


def main():
    root = Tk()
    graph = Graph()
    app = App(root, graph, 800, 650)

    if len(sys.argv) == 3 and sys.argv[1] == '-s':
        with open(sys.argv[2], 'r') as file:
            source = file.readlines()
    else:
        source = sys.stdin.readlines()
    source = deque(source)
    parse_ants(graph, source)
    parse_rooms(graph, source)
    parse_lines(graph, source)
    app.create_lines(graph)
    app.create_rooms(graph)
    app.canvas.pack()

    graph.get_paths()
    #print(graph.paths)

    ants = [1, 2, 3]
    shortest = min(graph.paths, key=len)

    steps = []
    for ant in ants:
        steps.append(["L{}-{}".format(ant, room) for room in shortest[1:]])

    graph.add_steps(steps)
    graph.add_ants(ants)
    graph.find_groups()

    root.mainloop()


if __name__ == "__main__":
    main()
