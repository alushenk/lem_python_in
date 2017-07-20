import sys


def parse_ants(graph):
    number_of_ants = sys.stdin.readline().rstrip('\n')
    if not number_of_ants.isdigit():
        print('Error! parameter not a digit')
        exit()
    graph.number_of_ants = number_of_ants


def parse_rooms(graph):
    for line in sys.stdin:
        line = line.rstrip('\n')
        if line == '##start':
            line = sys.stdin.readline().rstrip('\n')
            graph.add_start(*line.split(" ", 3))
            continue
        if line == '##end':
            line = sys.stdin.readline().rstrip('\n')
            graph.add_end(*line.split(" ", 3))
            break
        if line.startswith("#"):
            continue
        graph.add_room(*line.split(" ", 3))


def parse_lines(graph):
    for line in sys.stdin:
        if line.startswith("#"):
            continue
        line = line.rstrip('\n')
        graph.add_line(*line.split("-", 2))
