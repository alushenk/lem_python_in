import sys
from room import Room
from ant import Ant
from collections import deque


class Graph(object):
    def __init__(self):
        self.rooms = {}
        self.lines = []
        self.ants = []
        self.steps = None
        self.start_room = None
        self.end_room = None
        self.path = None
        self.paths = None

    def add_room(self, name, x, y):
        room = Room(name, x, y)
        self.rooms[name] = room
        return room

    def add_start(self, name, x, y):
        self.start_room = self.add_room(name, x, y)

    def add_end(self, name, x, y):
        self.end_room = self.add_room(name, x, y)

    def add_line(self, a, b):
        if a in self.rooms and b in self.rooms:
            self.rooms[a].add_connection(b)
            self.rooms[b].add_connection(a)
            self.lines.append((a, b))
        else:
            print('Error! linking non-existent rooms')
            sys.exit()

    def print_rooms(self):
        for name, room in self.rooms.items():
            print(name + ': ' + ', '.join(room.connections) + '\n')

    def print_lines(self):
        for elem in self.lines:
            a, b = elem
            print('{0} {1}'.format(a, b))

    def add_steps(self, steps):
        self.steps = steps

    def add_ants(self, ants):
        for name in ants:
            ant = Ant(name, self.start_room.x, self.start_room.y)
            self.ants.append(ant)

    def add_path(self, path):
        self.path = path

    def get_paths(self):
        self.paths = self.find_all_paths(self.rooms, self.start_room.name, self.end_room.name)

    def find_all_paths(self, graph, start, end, path=[]):
        path = path + [start]
        if start == end:
            return [path]
        if start not in graph or end not in graph or len(graph[end].connections) == 0:
            return []
        paths = []
        for node in graph[start].connections:
            if node not in path:
                newpaths = self.find_all_paths(graph, node, end, path)
                for newpath in newpaths:
                    paths.append(newpath)
        return paths

    def get_path(self):
        self.path = self.find_path(self.rooms, self.start_room.name, self.end_room.name)

    def find_path(self, graph, start, end, path=[]):
        path = path + [start]
        if start == end:
            return path
        if start not in graph or end not in graph or len(graph[end].connections) == 0:
            return None
        for node in graph[start].connections:
            if node not in path:
                newpath = self.find_path(graph, node, end, path)
                if newpath:
                    return newpath
        return None

    def find_groups(self):
        sets = [set(x) for x in self.paths]
        suka = {self.start_room.name, self.end_room.name}

        tuple_paths = [tuple(path) for path in self.paths]

        paths = list(zip(sets, tuple_paths))
        groups = {(path,) for path in tuple_paths}
        for i, j in paths:
            group = {j}
            for a, b in paths:
                if (i & a) == suka:
                    group.add(b)
            groups.add(tuple(group))
        print(groups)
