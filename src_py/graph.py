import sys
from .room import Room
from .ant import Ant
from .path import Path
from .path_group import Group
from operator import attrgetter
from collections import deque


class Graph(object):
    def __init__(self):
        self.rooms = {}
        self.lines = []
        self.ants = None
        self.number_of_ants = 0
        self.steps = []
        self.start_room = None
        self.end_room = None
        self.paths = []
        self.path_groups = []
        self.chosen_group = None

    def add_room(self, name, x, y):
        room = Room(name, x, y)
        if name in self.rooms:
            print("Error! duplicate room name found")
            sys.exit()
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
        print('##start')
        print('{0} {1} {2}'.format(self.start_room.name, self.start_room.x, self.start_room.y))
        for room in self.rooms.values():
            if room.name != self.start_room.name and room.name != self.end_room.name:
                print('{0} {1} {2}'.format(room.name, room.x, room.y))
        print('##end')
        print('{0} {1} {2}'.format(self.end_room.name, self.end_room.x, self.end_room.y))

    def print_lines(self):
        for elem in self.lines:
            a, b = elem
            print('{0}-{1}'.format(a, b))

    def print_steps(self):
        for step in self.steps:
            print(' '.join(step))

    def print_groups(self):
        for group in self.path_groups:
            for path in group.paths:
                print(path.rooms)
            print(group.efficiency_coef)
            print()

    def print_chosen_group(self):
        print('-' * 50)
        for i, path in enumerate(self.chosen_group.paths):
            print(path.rooms)
            print(self.chosen_group.ants_counters[i])
        print()
        print(self.chosen_group.efficiency_coef)
        print('-' * 50)

    def add_ants(self):
        ants = []
        for name in range(1, self.number_of_ants + 1):
            ant = Ant(name, self.start_room.x, self.start_room.y)
            ants.append(ant)
        self.ants = ants

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

    # тупой перебор сложностью О(n^3)
    # сделать с помощью матрицы путей(не смежности)
    def find_path_groups(self):
        resulting_groups = []
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
            group = tuple(group)
            if group not in resulting_groups:
                resulting_groups.append(group)

        for group in resulting_groups:
            self.path_groups.append(Group(group))

    def chose_path_group(self):
        groups = self.path_groups
        if not groups:
            print("Error! no paths found")
            sys.exit()
        number_of_ants = self.number_of_ants
        for group in groups:
            for i in range(number_of_ants):
                # path wiht minimal traffic
                free_way = min(group.paths, key=attrgetter('weight'))
                # index of path which has minimal traffic
                free_way_index = group.paths.index(free_way)
                # incremented ants of the less loaded path
                group.ants_counters[free_way_index] += 1
                free_way.weight += 1

            heaviest_path = max(group.paths, key=attrgetter('weight'))
            group.efficiency_coef = heaviest_path.weight
        self.chosen_group = min(groups, key=attrgetter('efficiency_coef'))

    def generate_steps(self):
        group = self.chosen_group
        index = 0
        for i, path in enumerate(group.paths):
            ants_count = group.ants_counters[i]
            self.create_steps(self.rooms, path, self.ants[index:index + ants_count], self.end_room)
            index += ants_count

        while True:
            empty = 0
            step = []
            for path in group.paths:
                if path.steps:
                    step += path.steps.popleft()
                else:
                    empty += 1
            if empty == group.paths_count:
                break
            self.steps.append(step)

    @staticmethod
    def create_steps(rooms, path, ants, end_room):
        steps = []
        index = 0
        while ants:
            step = []
            current_index = index
            for ant in ants:
                if current_index < 0:
                    break
                current_room = rooms[path.rooms[current_index]]
                next_room = rooms[path.rooms[current_index + 1]]
                if next_room.is_free():
                    next_room.add_ant(current_room.pop_ant())
                    step.append("L{0}-{1}".format(ant, next_room))
                    current_index -= 1
                    if next_room == end_room:
                        end_room.pop_ant()
                        ants = ants[1:]
                        index -= 1
            steps.append(step)
            index += 1
        path.steps = deque(steps)
