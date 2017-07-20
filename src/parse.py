def parse_ants(graph, number_of_ants):
    if not number_of_ants.isdigit():
        print('Error! parameter not a digit')
        exit()
    graph.number_of_ants = number_of_ants


def parse_rooms(graph, source):
    while source:
        line = source.popleft().rstrip('\n')
        if line == '##start':
            line = source.popleft().rstrip('\n') if source else None
            graph.add_start(*line.split(" ", 3))
            continue
        if line == '##end':
            line = source.popleft().rstrip('\n') if source else None
            graph.add_end(*line.split(" ", 3))
            break
        if line.startswith("#"):
            continue
        graph.add_room(*line.split(" ", 3))


def parse_lines(graph, source):
    while source:
        line = source.popleft().rstrip('\n')
        if line.startswith("#"):
            continue
        line = line.rstrip('\n')
        graph.add_line(*line.split("-", 2))
