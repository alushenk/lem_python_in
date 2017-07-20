from tkinter import *
import time


class App(object):
    def __init__(self, master, graph, width, height):
        self.master = master
        self.graph = graph
        self.width = width
        self.height = height
        self.init_window()
        self.bind_buttons()
        self.canvas = Canvas(
            self.master,
            bg="white",
            height=height,
            width=width
        )
        self.ball = self.canvas.create_oval(
            0, 25, 25, 50,
            fill='yellow',
            outline="#666699",
            width=3
        )
        self.button = Button(
            self.master,
            text="QUIT",
            fg="red",
            command=quit
        )
        self.button.pack(side=BOTTOM)
        self.slogan = Button(
            self.master,
            text="Hello",
            command=self.update_graph
        )
        self.slogan.pack(side=BOTTOM)

    def init_window(self):
        # calculate x and y coordinates for the Tk root window
        x = (self.master.winfo_screenwidth() / 2) - (self.width / 2)
        y = (self.master.winfo_screenheight() / 2) - (self.height / 2)

        # set the dimensions of the screen
        # and where it is placed
        self.master.geometry('%dx%d+%d+%d' % (self.width, self.height, x, y))

    def bind_buttons(self):
        self.master.bind('<Escape>', self.close)
        self.master.bind('<Key>', self.press)
        self.master.bind('<Button-1>', self.motion)

    def press(self, event):
        # print(event.keycode)
        if event.keycode == 114:
            self.canvas.move(self.ball, 10, 0)
        if event.keycode == 113:
            self.canvas.move(self.ball, -10, 0)
        if event.keycode == 111:
            self.canvas.move(self.ball, 0, -10)
        if event.keycode == 116:
            self.canvas.move(self.ball, 0, 10)
        if event.keycode == 65:
            self.canvas.move(self.ball, 10, 10)

    @staticmethod
    def close(event):
        sys.exit()

    @staticmethod
    def motion(event):
        print("Mouse position: (%s %s)" % (event.x, event.y))

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
            self.canvas.create_text(
                room.x,
                room.y,
                text=room.name
            )

    def update_graph(self):
        for room in self.graph.rooms.values():
            self.canvas.itemconfig(room.oval, fill="black")
            self.canvas.update()
            time.sleep(0.5)
