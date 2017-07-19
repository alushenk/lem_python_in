#!../bin/python3

import sys


def main():

    rooms = {}
    lines = {}

    number_of_ants = sys.stdin.readline()
    if not number_of_ants[:-1].isdigit():
        print ('Error! parameter not a digit')
        exit()

    for line in sys.stdin:
        if line == '##start':
            startroom = sys.stdin.readline()
            continue
        if line == '##end':
            endroom = sys.stdin.readline()
            continue
        if line.startswith("#"):
            continue
        print(line[:-1])


if __name__ == "__main__":
    main()
