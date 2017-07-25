from operator import attrgetter


class Group(object):
    def __init__(self, paths):
        self.paths = sorted(paths, key=attrgetter('length'))
        self.paths_count = len(paths)
        self.efficiency_coef = 0
        paths = []
