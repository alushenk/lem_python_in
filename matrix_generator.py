#!/usr/bin/env python3
import sys
import os

def generate_matrix(file, x, y):
    matrix = []
    i = 0
    for a in range(y):
        line = []
        for b in range(x):
            line.append((i, b, a))
            i += 1
        matrix.append(line)

    connections = []
    for a in range(y):
        for b in range(x):
            if b + 1 < x:
                connections.append((matrix[a][b][0], matrix[a][b + 1][0]))
            if a + 1 < y:
                connections.append((matrix[a][b][0], matrix[a + 1][b][0]))

    file.write('20\n##start\n')
    for i, line in enumerate(matrix):
        for j, elem in enumerate(line):
            if i + 1 == y and j + 1 == x:
                file.write('##end\n')
            file.write('{} {} {}\n'.format(*elem))

    for line in connections:
        file.write('{}-{}\n'.format(*line))

if __name__ == "__main__":
    length = len(sys.argv)
    if length == 4:
        path = sys.argv[1]
        basedir = os.path.dirname(path)
        if basedir and not os.path.exists(basedir):
            os.makedirs(basedir)
        with open(path, 'w') as file:
            x = int(sys.argv[2])
            y = int(sys.argv[3])
            generate_matrix(file, x, y)
    else:
        print("usage: [output file name] [x] [y]")