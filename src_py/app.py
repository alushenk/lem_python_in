from tkinter import *
import time
from threading import Thread

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
        self.t = None

        self.room_color_ending = '#60d6ca'
        self.room_outline_ending = '#666699'
        self.room_color = '#ff6666'
        self.room_outline = '#666699'
        self.ant_color = 'yellow'
        self.ant_outline = '#666699'
        self.line_color = '#666699'
        self.line_width = 4
        self.shape_radius = 15
        self.shape_radius_ending = 16
        self.shape_outline_width = 3

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

        self.move_button = Button(
            self.frame,
            text="start",
            command=self.start
        )
        self.move_button.pack(side=LEFT)

        self.scale = Scale(
            self.frame,
            from_=100,
            to=0,
            orient=HORIZONTAL,
            length=300
        )
        self.scale.set(50)
        self.scale.pack(side=LEFT)

    def init_window(self):
        # calculate x and y coordinates for the Tk root window
        x = (self.master.winfo_screenwidth() / 2) - (self.width / 2)
        y = (self.master.winfo_screenheight() / 2) - (self.height / 2)
        # set the dimensions of the screen
        # and where it is placed
        self.master.geometry('%dx%d+%d+%d' % (self.width, self.height, x, y))

    def bind_buttons(self):
        self.master.bind('<Escape>', quit)
        # self.master.bind('<Key>', self.press)

    def safe_escape(self):
        pass

    def create_lines(self, graph):
        lines = graph.lines
        rooms = graph.rooms
        for elem in lines:
            a, b = elem
            a = rooms[a]
            b = rooms[b]
            self.canvas.create_line(
                a.x, a.y, b.x, b.y,
                fill=self.line_color,
                width=self.line_width)

    def create_rooms(self, graph):
        rooms = graph.rooms
        for room in rooms.values():
            radius = self.shape_radius
            room_color = self.room_color
            room_outline = self.room_outline
            if room == self.graph.start_room or room == self.graph.end_room:
                radius = self.shape_radius_ending
                room_color = self.room_color_ending
                room_outline = self.room_outline_ending
            room.oval = self.canvas.create_oval(
                room.x - radius, room.y - radius,
                room.x + radius, room.y + radius,
                fill=room_color,
                outline=room_outline,
                width=self.shape_outline_width
            )
            room.number = self.canvas.create_text(
                room.x,
                room.y,
                text=room.name
            )

    def create_ants(self):
        radius = self.shape_radius
        for ant in self.graph.ants:
            ant.oval = self.canvas.create_oval(
                ant.x - radius, ant.y - radius,
                ant.x + radius, ant.y + radius,
                fill=self.ant_color,
                outline=self.ant_outline,
                width=self.shape_outline_width
            )
            ant.number = self.canvas.create_text(
                ant.x,
                ant.y,
                text=ant.name
            )
            self.canvas.update()

    def start(self):
        if not self.t:
            self.t = Thread(target=self.move_ants)
            self.t.start()

    def move_ants(self):
        self.graph.add_ants()
        self.create_ants()
        divider = 30
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
                time.sleep(self.scale.get() / 5000)

        for ant in self.graph.ants:
            self.canvas.delete(ant.oval)
            self.canvas.delete(ant.number)

        self.t = None
