# lem_python_in
project about graphs and data visualisation

main.py - algorithm along with visualisation
lem_in.py - only algorithm with stardard output into console
visualise.py - only visualisation without algorithm. reads commands from standard input

usage examples:

./lem_in.py < files/file_4

./lem_in.py -s files/file_4

./lem_in.py < files/file_4 | ./visualise.py

./main.py < files/file_4

./main.py -s files/file_4

input file description:

number_of_ants
the_rooms
the_links
the_steps

step:
Lx-y Lz-w Lr-o ...
x, z, r represents the ants’ numbers (going from 1 to number_of_ants) and y,
w, o represents the rooms’ names.
