from tkinter import *
import time

# up, left, down, right
MAC_ARROWS = (8320768, 8124162, 8255233, 8189699)
UBUNTU_ARROWS = (111, 113, 116, 114)

ARROWS = MAC_ARROWS


class App(object):
    def __init__(self, master, graph, width, height):
        self.master = master
        self.graph = graph
        self.width = width
        self.height = height
        self.init_window()
        self.bind_buttons()
        self.frame = Frame(
            self.master
        )
        self.frame.pack(side=BOTTOM)
        self.canvas = Canvas(
            self.master,
            bg="white",
            height=height,
            width=width
        )
        self.exit_button = Button(
            self.frame,
            text="QUIT",
            fg="red",
            command=quit
        )
        self.exit_button.pack(side=LEFT)
        self.run_button = Button(
            self.frame,
            text="animate",
            command=self.update_graph
        )
        self.run_button.pack(side=LEFT)
        self.create_button = Button(
            self.frame,
            text="add ants",
            command=self.create_ants
        )
        self.create_button.pack(side=LEFT)
        self.move_button = Button(
            self.frame,
            text="move ants",
            command=self.move_ants
        )
        self.move_button.pack(side=LEFT)

    def init_window(self):
        # calculate x and y coordinates for the Tk root window
        x = (self.master.winfo_screenwidth() / 2) - (self.width / 2)
        y = (self.master.winfo_screenheight() / 2) - (self.height / 2)
        # set the dimensions of the screen
        # and where it is placed
        self.master.geometry('%dx%d+%d+%d' % (self.width, self.height, x, y))

    def bind_buttons(self):
        self.master.bind('<Escape>', sys.exit)
        # self.master.bind('<Key>', self.press)

    def create_lines(self, graph):
        lines = graph.lines
        rooms = graph.rooms
        for elem in lines:
            a, b = elem
            a = rooms[a]
            b = rooms[b]
            self.canvas.create_line(a.x, a.y, b.x, b.y, fill='#666699', width=4)

    def create_rooms(self, graph):
        rooms = graph.rooms
        for room in rooms.values():
            room.oval = self.canvas.create_oval(
                room.x - 15, room.y - 15,
                room.x + 15, room.y + 15,
                fill='#ff6666',
                outline="#666699",
                width=3
            )
            room.number = self.canvas.create_text(
                room.x,
                room.y,
                text=room.name
            )

    def update_graph(self):
        for room in self.graph.rooms.values():
            self.canvas.itemconfig(room.oval, fill="black")
            self.canvas.update()
            time.sleep(0.5)

    def create_ants(self):
        for ant in self.graph.ants:
            ant.oval = self.canvas.create_oval(
                ant.x - 15, ant.y - 15,
                ant.x + 15, ant.y + 15,
                fill='yellow',
                outline="#666699",
                width=3
            )
            ant.number = self.canvas.create_text(
                ant.x,
                ant.y,
                text=ant.name
            )
            self.canvas.update()

    def move_ants(self):
        divider = 10
        for line in self.graph.steps:
            steps = []
            for step in line:
                ant, dest = step.split('-', 2)
                ant = self.graph.ants[int(ant[1:]) - 1]
                dest = self.graph.rooms[dest]
                delta_x = dest.x - ant.x
                delta_y = dest.y - ant.y
                ant.x += delta_x
                ant.y += delta_y
                move_x = delta_x / divider
                move_y = delta_y / divider
                steps.append((ant, move_x, move_y))

            for i in range(divider):
                for ant, move_x, move_y in steps:
                    self.canvas.move(ant.oval, move_x, move_y)
                    self.canvas.move(ant.number, move_x, move_y)
                self.canvas.update()
                time.sleep(0.05)
                # time.sleep(0.025)
