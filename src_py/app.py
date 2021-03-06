from tkinter import *
from threading import Thread
from collections import deque
from operator import attrgetter

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
        self.steps = None
        self.step = None
        self.smothnes = None
        self.divider = 1
        self.paused = 1
        self.stopped = 0

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
            text="quit",
            fg="red",
            command=quit
        )
        self.exit_button.pack(side=LEFT)

        self.reset_button = Button(
            self.frame,
            text="reset",
            command=self.reset
        )
        self.reset_button.pack(side=LEFT)

        self.start_text = StringVar()
        self.start_text.set("start")

        self.move_button = Button(
            self.frame,
            textvariable=self.start_text,
            command=self.start
        )
        self.move_button.pack(side=LEFT)

        self.scale = Scale(
            self.frame,
            from_=200,
            to=1,
            orient=HORIZONTAL,
            length=300
        )
        self.scale.set(20)
        self.scale.pack(side=LEFT)

        self.smooth = Scale(
            self.frame,
            from_=1,
            to=100,
            orient=HORIZONTAL,
            length=100
        )
        self.smooth.set(20)
        self.smooth.pack(side=LEFT)

    def init_window(self):
        # calculate x and y coordinates for the Tk root window
        x = (self.master.winfo_screenwidth() / 2) - (self.width / 2)
        y = (self.master.winfo_screenheight() / 2) - (self.height / 2)
        # set the dimensions of the screen
        # and where it is placed
        self.master.geometry('%dx%d+%d+%d' % (self.width, self.height, x, y))

    def configure_scale(self):
        rooms = list(self.graph.rooms.values())
        min_x = min(rooms, key=attrgetter('x')).x
        min_y = min(rooms, key=attrgetter('y')).y
        max_x = max(rooms, key=attrgetter('x')).x
        max_y = max(rooms, key=attrgetter('y')).y

        plot_min_x = self.shape_radius * 2
        plot_max_x = self.width - plot_min_x
        plot_min_y = self.shape_radius
        plot_max_y = self.height - plot_min_y - 100

        delta_x = (plot_max_x - plot_min_x) / (max_x - min_x)
        delta_y = (plot_max_y - plot_min_y) / (max_y - min_y)

        for room in rooms:
            room.x *= delta_x
            room.y *= delta_y

        min_x = min(rooms, key=attrgetter('x')).x
        min_y = min(rooms, key=attrgetter('y')).y
        max_x = max(rooms, key=attrgetter('x')).x
        max_y = max(rooms, key=attrgetter('y')).y

        plot_cent_x = self.width / 2
        plot_cent_y = (self.height - 50) / 2

        graph_cent_x = min_x + (max_x - min_x) / 2
        graph_cent_y = min_y + (max_y - min_y) / 2

        cent_x = graph_cent_x - plot_cent_x
        cent_y = graph_cent_y - plot_cent_y

        for room in rooms:
            room.x -= cent_x
            room.y -= cent_y

    def bind_buttons(self):
        self.master.bind('<Escape>', self.safe_exit)
        # self.master.bind('<Key>', self.press)

    def safe_exit(self, code):
        quit()

    def create_lines(self):
        lines = self.graph.lines
        rooms = self.graph.rooms
        for elem in lines:
            a, b = elem
            a = rooms[a]
            b = rooms[b]
            self.canvas.create_line(
                a.x, a.y, b.x, b.y,
                fill=self.line_color,
                width=self.line_width)

    def create_rooms(self):
        rooms = self.graph.rooms
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

    def start(self):
        if not self.t:
            self.stopped = 0
            self.smooth.config(state=DISABLED, takefocus=0)
            self.t = Thread(target=self.move_ants)
            self.t.start()
        if self.paused:
            self.start_text.set("pause")
            self.paused = 0
        else:
            self.start_text.set(" play  ")
            self.paused = 1

    def reset(self):
        if self.t:
            self.stopped = 1
            self.t = None
            self.start_text.set(" play  ")
            self.scale.config(state=ACTIVE, takefocus=1)
            self.smooth.config(state=ACTIVE, takefocus=1)
            self.paused = 1
            for elem in self.step:
                if elem[0].oval:
                    self.canvas.delete(elem[0].oval)
                    self.canvas.delete(elem[0].number)

    def move_ants(self):
        self.graph.add_ants()
        self.divider = self.smooth.get()
        steps = []
        for step in self.graph.steps:
            moves = []
            for move in step:
                ant, dest = move.split('-', 2)
                ant = self.graph.ants[int(ant[1:]) - 1]
                dest = self.graph.rooms[dest]
                delta_x = dest.x - ant.x
                delta_y = dest.y - ant.y
                ant.x += delta_x
                ant.y += delta_y
                move_x = delta_x / self.divider
                move_y = delta_y / self.divider
                if dest == self.graph.end_room:
                    delete = 1
                else:
                    delete = 0
                moves.append((ant, move_x, move_y, delete))
            steps.append(moves)

        self.steps = deque(steps)
        self.step = self.steps.popleft()
        self.smothnes = self.smooth.get()
        self.move()

    def move(self):
        if self.stopped:
            return
        if self.paused:
            self.master.after(1, self.move)
            return
        self.divider -= 1
        for ant, move_x, move_y, delete in self.step:
            if not ant.oval:
                radius = self.shape_radius
                x = self.graph.start_room.x
                y = self.graph.start_room.y
                ant.oval = self.canvas.create_oval(
                    x - radius, y - radius,
                    x + radius, y + radius,
                    fill=self.ant_color,
                    outline=self.ant_outline,
                    width=self.shape_outline_width
                )
                ant.number = self.canvas.create_text(x, y, text=ant.name)
            self.canvas.move(ant.oval, move_x, move_y)
            self.canvas.move(ant.number, move_x, move_y)
            if delete and self.divider == 0:
                self.canvas.delete(ant.oval)
                self.canvas.delete(ant.number)
        if self.divider > 0:
            self.master.after(self.scale.get(), self.move)
        else:
            if self.steps:
                self.step = self.steps.popleft()
                self.divider = self.smothnes
                self.master.after(self.scale.get(), self.move)
            else:
                self.start_text.set(" start ")
                self.scale.config(state=ACTIVE, takefocus=1)
                self.smooth.config(state=ACTIVE, takefocus=1)
                self.paused = 1
                self.t = None
