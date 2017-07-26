import sys
from .room import Room
from .ant import Ant
from .path import Path
from .path_group import Group
from operator import itemgetter
from collections import deque
import math


class Graph(object):
    def __init__(self):
        self.rooms = {}
        self.lines = []
        self.ants = []
        self.number_of_ants = 0
        self.steps = []
        self.start_room = None
        self.end_room = None
        self.paths = []
        self.path_groups = []
        self.chosen_group = None

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
            print(step)

    def print_groups(self):
        for group in self.path_groups:
            for path in group.paths:
                print(path.rooms)
            print(group.efficiency_coef)
            print()
            # print(' | '.join([' '.join(path.rooms) for path in group]) + '\n')

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
        paths = sorted(paths, key=len)
        for i, path in enumerate(paths):
            self.paths.append(Path(path, i))

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
        resulting_groups = set()
        paths = self.paths
        endings = {self.start_room.name, self.end_room.name}
        for a in paths:
            group = [a]
            for b in paths:
                if a.index == b.index:
                    continue
                for c in group:
                    if c.set & b.set != endings:
                        break
                else:
                    i = 0
                    for path in group:
                        if b.index < path.index:
                            break
                        i += 1
                    group.insert(i, b)
            resulting_groups.add(tuple(group))

        for group in resulting_groups:
            self.path_groups.append(Group(group))

    def choose_path_group(self):

        for group in self.path_groups:
            part_ants = self.number_of_ants // group.paths_count
            total_weight = sum(x.length for x in group.paths)
            average_length = total_weight // group.paths_count

            for i, path in enumerate(group.paths):
                displacement = average_length - path.length
                group.ants_counters[i] = part_ants + displacement

            while sum(group.ants_counters) < self.number_of_ants:
                # index of group which has minimal amount of ants
                min_index = group.ants_counters.index(min(group.ants_counters))
                # incremented ants of the shorter path of the current group
                group.ants_counters[min_index] += 1

            group.average = average_length
            max_ants_index, max_ants_value = max(enumerate(group.ants_counters), key=lambda x: x[1])
            maximum_ants_path = group.paths[max_ants_index]
            group.efficiency_coef = max_ants_value + maximum_ants_path.length
        self.chosen_group = min(self.path_groups, key=lambda x: x.efficiency_coef)

    def generate_steps(self):
        group = self.chosen_group
        start_index = 0
        for i, path in enumerate(group.paths):
            self.create_steps(path, self.ants[start_index:start_index + group.ants_counters[i]])
            start_index += group.ants_counters[i]

        while True:
            empty = 0
            step = []
            for path in group.paths:
                if path.steps:
                    step += path.steps.popleft()
                else:
                    empty += 1
            self.steps.append(step)
            if empty == self.chosen_group.paths_count:
                break

    def create_steps(self, path, ants):
        steps = []
        index = 0
        while ants:
            step = []
            current_index = index
            for ant in ants:
                if current_index < 0:
                    break
                next_index = current_index + 1
                current_room = self.rooms[path.rooms[current_index]]
                next_room = self.rooms[path.rooms[next_index]]
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
        path.steps = deque(steps)
