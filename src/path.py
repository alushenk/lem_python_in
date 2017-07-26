class Path(object):
    def __init__(self, rooms, index):
        # может добавить классы Room чтобы в graph.generate_steps() было удобней
        self.index = index
        self.rooms = tuple(rooms)
        self.set = set(rooms)
        self.length = len(rooms)
        self.steps = 0
