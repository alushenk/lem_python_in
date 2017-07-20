from tkinter import *  # note that module name has changed from Tkinter in Python 2 to tkinter in Python 3
import sys


def motion(event):
    print("Mouse position: (%s %s)" % (event.x, event.y))
    return


def size_init(root):
    w = 800  # width for the Tk root
    h = 650  # height for the Tk root

    # get screen width and height
    ws = root.winfo_screenwidth()  # width of the screen
    hs = root.winfo_screenheight()  # height of the screen

    # calculate x and y coordinates for the Tk root window
    x = (ws / 2) - (w / 2)
    y = (hs / 2) - (h / 2)

    # set the dimensions of the screen
    # and where it is placed
    root.geometry('%dx%d+%d+%d' % (w, h, x, y))


def close(event):
    sys.exit()


def graphic(rooms, lines):
    def press(event):
        print(event.keycode)
        if event.keycode == 114:
            canvas.move(ball, 10, 0)
        if event.keycode == 113:
            canvas.move(ball, -10, 0)
        if event.keycode == 111:
            canvas.move(ball, 0, -10)
        if event.keycode == 116:
            canvas.move(ball, 0, 10)
        if event.keycode == 65:
            canvas.move(ball, 10, 10)

    root = Tk()
    root.bind('<Escape>', close)
    root.bind('<Key>', press)
    size_init(root)

    canvas = Canvas(
        root,
        bg="#B0E0E6",
        height=root.winfo_screenheight(),
        width=root.winfo_screenwidth()
    )

    # canvas.create_text(200, 200, text="suka")
    canvas.bind('<Button-1>', motion)

    for elem in lines:
        a, b = elem
        a = rooms[a]
        b = rooms[b]
        print(b.x)
        print(b.y)
        # dash=(4, 4) - to make lines dashed
        canvas.create_line(a.x, a.y, b.x, b.y, fill='#033192', width=4)

    for room in rooms.values():
        room.oval = canvas.create_oval(
            room.x - 15, room.y - 15,
            room.x + 15, room.y + 15,
            fill='red',
            outline="blue",
            width=3
        )
        canvas.create_text(
            room.x,
            room.y,
            text=room.name
        )

    ball = canvas.create_oval(0, 25, 25, 50, fill='yellow', outline="blue", width=3)

    canvas.pack()
    root.mainloop()
