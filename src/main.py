from tkinter import *
from app import App
from graph import Graph
from parse import *
import sys
from collections import deque
import time


def find_shortest_path(root, graph, app):
    start = graph.start_room
    end = graph.end_room
    rooms = graph.rooms
    lines = graph.lines
    path = []
    while start != end and start not in path:
        root.after(1000)
        app.canvas.itemconfig(start.oval, fill="black")
        # app.canvas.update()
        path.append(start.name)
        for connection in start.connections:
            if connection in path:
                continue
            start = rooms[connection]
            break
    if start == end:
        path.append(start.name)
    return path


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
    parse_ants(graph, source.popleft().rstrip('\n'))
    parse_rooms(graph, source)
    parse_lines(graph, source)

    app.create_lines(graph)
    app.create_rooms(graph)

    app.canvas.pack()

    # path = find_shortest_path(root, graph, app)
    # print(', '.join(path))

    # current = 0
    # def update():
    #     if current == graph.end_room:
    #         break
    #
    #



    root.mainloop()


if __name__ == "__main__":
    main()
