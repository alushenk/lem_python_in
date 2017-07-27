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

    app.create_lines(graph)
    app.create_rooms(graph)
    app.canvas.pack()

    graph.get_paths()
    graph.add_ants()
    graph.find_path_groups()
    graph.chose_path_group()
    graph.generate_steps()

    print(graph.number_of_ants)
    graph.print_rooms()
    graph.print_lines()
    print()
    graph.print_steps()

    # root.mainloop()


if __name__ == "__main__":
    main()
