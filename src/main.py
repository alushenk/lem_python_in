import sys
from tkinter import *
from app import App
from graph import Graph
from room import Room
from ant import Ant


def main():
    root = Tk()
    app = App(root, 800, 650)
    graph = Graph()

    number_of_ants = sys.stdin.readline().rstrip('\n')
    if not number_of_ants.isdigit():
        print('Error! parameter not a digit')
        exit()

    for line in sys.stdin:
        line = line.rstrip('\n')
        if line == '##start':
            line = sys.stdin.readline().rstrip('\n')
            graph.add_start(*line.split(" ", 3))
            continue
        if line == '##end':
            line = sys.stdin.readline().rstrip('\n')
            graph.add_end(*line.split(" ", 3))
            break
        if line.startswith("#"):
            continue
        graph.add_room(*line.split(" ", 3))

    for line in sys.stdin:
        if line.startswith("#"):
            continue
        line = line.rstrip('\n')
        graph.add_line(*line.split("-", 2))

    graph.print_rooms()
    graph.print_lines()

    app.create_lines(graph)
    app.create_rooms(graph)

    # nahuya eto govno nado vashe?
    app.canvas.pack()
    root.mainloop()


if __name__ == "__main__":
    main()
