import sys
from .room import Room
from .ant import Ant
from .path import Path
from operator import itemgetter
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
        self.paths = []
        self.path_groups = None

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

    def print_groups(self):
        for group in self.path_groups:
            print(group)

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
        paths = self.find_all_paths(self.rooms, self.start_room.name, self.end_room.name)
        for path in paths:
            self.paths.append(Path(path))

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

    def find_path_groups(self):
        groups = {(path.rooms,) for path in self.paths}
        paths = self.paths
        for a in paths:
            group = {a.rooms}
            for b in paths:
                if a.set.isdisjoint(b.set) and a.len != 2:
                    group.add(b.rooms)
            if len(group) != 1:
                groups.add(tuple(sorted(group)))
        self.path_groups = groups

    # пока ищет по наименьшей сумме всех весов путей
    def choose_path_group(self):
        result = []

        for group in self.path_groups:
            length = 0
            for path in group:
                length += len(path)
            result.append((group, length))

        result = min(result, key=itemgetter(1))
        print('suka')
        print(result)

    def generate_steps(self):
        ants = self.ants
        path = self.paths[0].rooms

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
