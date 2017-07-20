from tkinter import *
import sys
from app import App


def graphic(rooms, lines):
    root = Tk()
    app = App(root, 800, 650)

    for elem in lines:
        a, b = elem
        a = rooms[a]
        b = rooms[b]
        print(b.x)
        print(b.y)
        # dash=(4, 4) - to make lines dashed
        app.canvas.create_line(a.x, a.y, b.x, b.y, fill='#033192', width=4)

    for room in rooms.values():
        room.oval = app.canvas.create_oval(
            room.x - 15, room.y - 15,
            room.x + 15, room.y + 15,
            fill='red',
            outline="blue",
            width=3
        )
        app.canvas.create_text(
            room.x,
            room.y,
            text=room.name
        )

    app.canvas.pack()
    root.mainloop()
