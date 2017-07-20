from tkinter import *


class App(object):
    def __init__(self, master, width, height):
        self.master = master
        self.width = width
        self.height = height
        self.init_window()
        self.bind_buttons()
        self.canvas = Canvas(
            self.master,
            bg="#B0E0E6",
            height=height,
            width=width
        )
        self.ball = self.canvas.create_oval(
            0, 25, 25, 50,
            fill='yellow',
            outline="blue",
            width=3
        )

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
        print(event.keycode)
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
