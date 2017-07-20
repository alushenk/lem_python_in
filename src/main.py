from tkinter import *
from app import App
from graph import Graph
from parse import *


def main():
    root = Tk()
    app = App(root, 800, 650)
    graph = Graph()

    parse_ants(graph)
    parse_rooms(graph)
    parse_lines(graph)

    app.create_lines(graph)
    app.create_rooms(graph)

    app.canvas.pack()
    root.mainloop()


if __name__ == "__main__":
    main()
