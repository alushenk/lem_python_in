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


def main():
    root = Tk()
    root.bind('<Escape>', close)
    size_init(root)

    canvas = Canvas(root, bg="#B0E0E6", height=root.winfo_screenheight(), width=root.winfo_screenwidth())

    canvas.create_text(200, 200, text="suka")
    canvas.bind('<Button-1>', motion)

    dots = {
        'a': (10, 20),
        'b': (30, 60),
        'c': (60, 90)
    }
    lines = {
        'a': 'b',
        'b': 'c'
    }

    for a, b in lines.items():
        canvas.create_line(dots[a][0] + 10, dots[a][1] + 10, dots[b][0] + 10, dots[b][1] + 10, fill='#033192')

    for x, y in dots.values():
        canvas.create_oval(x, y, x + 20, y + 20, fill='red')

    canvas.pack()

    root.mainloop()


main()
