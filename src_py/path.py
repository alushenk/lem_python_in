class Path(object):
    def __init__(self, rooms, index):
        # может добавить классы Room чтобы в graph.generate_steps() было удобней
        # и в chose_path_group не ебаться с индексами
        self.index = index
        self.rooms = tuple(rooms)
        self.set = set(rooms)
        self.weight = len(rooms)
