import sys
from .room import Room
from .ant import Ant
from collections import deque


class Graph(object):
    def __init__(self):
        self.rooms = {}
        self.lines = []
        self.ants = []
        self.number_of_ants = 0
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

    def print_steps(self):
        for step in self.steps:
            print(' '.join(step))

    def add_ants(self):
        for name in range(1, self.number_of_ants + 1):
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
        pass
        # for group in self.groups:
        #     for path in group:

    def generate_steps(self):
        ants = self.ants
        path = self.path

        steps = []
        index = 0
        while ants:
            step = []
            current_index = index
            for ant in ants:
                if current_index < 0:
                    break
                next_index = current_index + 1
                current_room = self.rooms[path[current_index]]
                next_room = self.rooms[path[next_index]]
                if next_room.is_free():
                    next_room.add_ant(current_room.pop_ant())
                    step.append("L{0}-{1}".format(ant, next_room))
                    current_index -= 1
                    if next_room == self.end_room:
                        self.end_room.pop_ant()
                        ants = ants[1:]
                        index -= 1
            steps.append(step)
            index += 1
        self.steps = steps
