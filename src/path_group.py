from operator import attrgetter


class Group(object):
    def __init__(self, paths):
        self.paths = sorted(paths, key=attrgetter('weight'))
        self.paths_count = len(paths)
        self.efficiency_coef = 0
        self.ants_counters = [0] * self.paths_count
