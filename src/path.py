class Path(object):
    def __init__(self, rooms):
        # может добавить классы Room чтобы в graph.generate_steps() было удобней
        self.rooms = tuple(rooms)
        self.set = set(rooms[1:-1])
        self.len = len(rooms)