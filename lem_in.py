#!/usr/bin/python3

from src_py.graph import Graph
from src_py.parse import *


def main():
    graph = Graph()

    source = get_source()

    parse_ants(graph, source)
    parse_rooms(graph, source)
    if not graph.start_room or not graph.end_room:
        print('Error! not enough data')
        exit()
    parse_lines(graph, source)

    graph.get_paths()
    graph.add_ants()
    graph.find_path_groups()
    graph.chose_path_group()
    graph.generate_steps()

    print(graph.number_of_ants)
    graph.print_rooms()
    graph.print_lines()
    print()
    graph.print_steps()


if __name__ == "__main__":
    main()
