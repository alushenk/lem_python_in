from tkinter import *
from src.app import App
from src.graph import Graph
from src.parse import *
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
    parse_data(graph, source)

    app.create_lines(graph)
    app.create_rooms(graph)
    app.canvas.pack()

    graph.get_paths()
    graph.add_ants()
    graph.find_path_groups()
    graph.chose_path_group()
    graph.print_chosen_group()
    graph.print_groups()
    graph.generate_steps()
    graph.print_steps()

    root.mainloop()


if __name__ == "__main__":
    main()
