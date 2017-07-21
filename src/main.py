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


def find_path(graph, start, end, path=[]):
    path = path + [start]
    if start == end:
        return path
    if start not in graph or end not in graph:
        return None
    for node in graph[start].connections:
        if node not in path:
            newpath = find_path(graph, node, end, path)
            if newpath:
                return newpath
    return None


def find_all_paths(graph, start, end, path=[]):
    path = path + [start]
    if start == end:
        return [path]
    if start not in graph or end not in graph:
        return []
    paths = []
    for node in graph[start].connections:
        if node not in path:
            newpaths = find_all_paths(graph, node, end, path)
            for newpath in newpaths:
                paths.append(newpath)
    return paths


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

    # path = find_shortest_path(root, graph, app)
    # print(', '.join(path))
    path = find_all_paths(graph.rooms, graph.start_room.name, graph.end_room.name)
    print(path)

    ants = deque([1, 2, 3])

    for room in path:
        ant = ants.popleft()


    steps = [
        ['L1-2', 'L2-6', 'L3-3'],
        ['L1-5', 'L2-4'],
        ['l3-2']
    ]
    graph.add_steps(steps)
    graph.add_ants(ants)
    graph.add_path(path)

    root.mainloop()


if __name__ == "__main__":
    main()
