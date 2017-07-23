import sys
from room import Room
from ant import Ant
from collections import deque


class Graph(object):
    def __init__(self):
        self.rooms = {}
        self.lines = []
        self.ants = []
        self.ants_count = None
        self.steps = None
        self.start_room = None
        self.end_room = None
        self.path = None
        self.paths = None
        self.groups = None

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

    def add_ants(self, ants):
        self.ants_count = len(ants)
        for name in ants:
            ant = Ant(name, self.start_room.x, self.start_room.y)
            self.ants.append(ant)

    def get_paths(self):
        if self.start_room.name not in self.rooms \
                or self.end_room.name not in self.rooms \
                or len(self.start_room.connections) == 0 \
                or len(self.end_room.connections) == 0:
            return
        self.paths = self.find_all_paths(self.rooms, self.start_room.name, self.end_room.name)
        self.path = min(self.paths, key=len)

    def find_all_paths(self, graph, start, end, path=[]):
        path = path + [start]
        if start == end:
            return [path]
        paths = []
        for node in graph[start].connections:
            if node not in path:
                newpaths = self.find_all_paths(graph, node, end, path)
                for newpath in newpaths:
                    paths.append(newpath)
        return paths

    def get_path(self):
        if self.start_room.name not in self.rooms \
                or self.end_room.name not in self.rooms \
                or len(self.start_room.connections) == 0 \
                or len(self.end_room.connections) == 0:
            return
        self.path = self.find_path(self.rooms, self.start_room.name, self.end_room.name)

    def find_path(self, graph, start, end, path=[]):
        path = path + [start]
        if start == end:
            return path
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
            buffer = [i]
            for a, b in paths:
                if (i & a) == suka:
                    not_exists = 1
                    for x in buffer:
                        if (x & a) != suka:
                            not_exists = 0
                    if not_exists:
                        group.add(b)
                        buffer.append(a)
            groups.add(tuple(group))
        self.groups = list(groups)

    def choose_path(self):
        self.path = self.groups[0][0]

        for group in self.groups:
            for path in group:

    def generate_steps(self):
        ants_count = self.ants_count
        ants = list(range(1, ants_count + 1))
        path = [[x, 0] for x in self.path]

        steps = []
        index = 0
        while ants_count > 0:
            step = []
            current_index = index
            for ant in ants:
                next_index = current_index + 1
                if path[next_index][1] == 0:
                    path[current_index][1] = 0
                    path[next_index][1] = 1
                    step.append("L{0}-{1}".format(ant, path[next_index][0]))
                    if current_index != 0:
                        current_index -= 1
                    if path[next_index][0] == self.end_room.name:
                        ants_count -= 1
                        ants = ants[1:]
                        index -= 1
            path[-1][1] = 0
            steps.append(step)
            index += 1
        self.steps = steps
