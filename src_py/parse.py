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


def parse_rooms(graph, source):
    while source:
        line = source.popleft().rstrip('\n')
        if line == '##start':
            line = source.popleft().rstrip('\n') if source else None
            errors_check(line)
            graph.add_start(*line.split(" ", 3))
            continue
        if line == '##end':
            line = source.popleft().rstrip('\n') if source else None
            errors_check(line)
            graph.add_end(*line.split(" ", 3))
            break
        if line.startswith("#"):
            continue
        errors_check(line)
        graph.add_room(*line.split(" ", 3))


def parse_lines(graph, source):
    while source:
        line = source.popleft()
        if line == '\n':
            break
        line = line.rstrip('\n')
        if line.startswith("#"):
            continue
        errors_check(line)
        graph.add_line(*line.split("-", 2))


def parse_steps(graph, source):
    while source:
        line = source.popleft().rstrip('\n')
        line = line.rstrip(' ')
        if line.startswith("#"):
            continue
        step = line.split(' ')
        graph.steps.append(step)
