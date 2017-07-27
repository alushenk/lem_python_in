#!/usr/bin/python3

from tkinter import *
from src_py.app import App
from src_py.graph import Graph
from src_py.parse import *
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
    if not graph.start_room or not graph.end_room:
        print('Error! not enough data')
        exit()
    parse_lines(graph, source)
    parse_steps(graph, source)

    graph.add_ants()
    app.create_lines(graph)
    app.create_rooms(graph)
    app.canvas.pack()

    root.mainloop()


if __name__ == "__main__":
    main()
