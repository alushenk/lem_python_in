#!/usr/bin/env python3
import sys
import os

def generate_matrix(file, x, y, start_name, end_name):
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
            if b + 1 < x and a + 1 < y:
            	connections.append((matrix[a][b][0], matrix[a + 1][b + 1][0]))
            	connections.append((matrix[a + 1][b][0], matrix[a][b + 1][0]))

    if end_name == 0:
    	end_name = matrix[-1][-1][0]
    file.write('20\n')
    for i, line in enumerate(matrix):
        for j, elem in enumerate(line):
        	if elem[0] == start_name:
        		file.write('##start\n')
        	if elem[0] == end_name:
        		file.write('##end\n')
        	file.write('{} {} {}\n'.format(*elem))

    for line in connections:
        file.write('{}-{}\n'.format(*line))

if __name__ == "__main__":
    length = len(sys.argv)
    start_name = 0
    end_name = 0
    if length == 6:
    	start_name = int(sys.argv[4])
    	end_name = int(sys.argv[5])
    	length -= 2
    if length == 5:
    	start_name = int(sys.argv[4])
    	length -= 1
    if length == 4:
        path = sys.argv[1]
        basedir = os.path.dirname(path)
        if basedir and not os.path.exists(basedir):
            os.makedirs(basedir)
        with open(path, 'w') as file:
            x = int(sys.argv[2])
            y = int(sys.argv[3])
            generate_matrix(file, x, y, start_name, end_name)
    else:
        print("usage: [output file name] [x] [y] [start name - optional] [end name - optional]")