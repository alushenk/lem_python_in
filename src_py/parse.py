import sys
from collections import deque


def get_source():
    if len(sys.argv) == 3 and sys.argv[1] == '-s':
        with open(sys.argv[2], 'r') as file:
            source = file.readlines()
    else:
        source = sys.stdin.readlines()
    if not source:
        exit()
    return deque(source)


def errors_check(line):
    if line.startswith("L") or line == '':
        print('Error! wrong parameters')
        exit()


def parse_ants(graph, source):
    number_of_ants = source.popleft().rstrip('\n')
    while number_of_ants.startswith("#"):
        number_of_ants = source.popleft().rstrip('\n')
    if not number_of_ants.isdigit():
        print('Error! parameter not a digit')
        exit()
    graph.number_of_ants = int(number_of_ants)


def is_room(line):
    if ' ' in line or line[0] == '#':
        return 1
    return 0


def get_room(line, n):
    params = line.split(" ")
    if len(params) != n:
        print('Error! wrong room')
        exit()
    return params


def parse_rooms(graph, source):
    while source and is_room(source[0]):
        line = source.popleft().rstrip('\n')
        if line == '##start':
            line = source.popleft().rstrip('\n') if source else None
            errors_check(line)
            graph.add_start(*get_room(line, 3))
            continue
        if line == '##end':
            line = source.popleft().rstrip('\n') if source else None
            errors_check(line)
            graph.add_end(*get_room(line, 3))
            continue
        if line.startswith("#"):
            continue
        errors_check(line)
        graph.add_room(*get_room(line, 3))


def parse_lines(graph, source):
    while source:
        line = source.popleft()
        if line == '\n':
            break
        line = line.rstrip('\n')
        if line.startswith("#"):
            continue
        errors_check(line)
        params = line.split("-")
        if len(params) != 2:
            print("Error! wrong connection")
            exit()
        graph.add_line(*params)


def parse_steps(graph, source):
    while source:
        line = source.popleft().rstrip('\n')
        line = line.rstrip(' ')
        if line.startswith("#"):
            continue
        step = line.split(' ')
        graph.steps.append(step)
