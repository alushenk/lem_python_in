#!../bin/python3

import matplotlib.pyplot as plt
import numpy as np


def draw_line():
    plt.plot([1, 2, 3, 4], [1, 4, 9, 16], 'ro')
    plt.axis([0, 6, 0, 20])
    # plt.ylabel('some numbers')


def draw_dots():
    t = np.arange(0., 5., 0.2)
    plt.plot(t, t, 'r--', t, t ** 2, 'bs', t, t ** 3, 'g^')


def dict_example():
    N = {
        'a': set('bcdef'),
        'b': set('ce'),
        'c': set('d')
    }


if __name__ == "__main__":
    draw_dots()
    plt.show()
