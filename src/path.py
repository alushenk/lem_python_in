class Path(object):
    def __init__(self, rooms):
        # может добавить классы Room чтобы в graph.generate_steps() было удобней
        self.rooms = tuple(rooms)
        self.set = set(rooms[1:-1])
        self.length = len(rooms)
        self.ants = 0

    def __add__(self, other):
        return self.length + other.length
