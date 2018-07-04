import numpy as np
import entpy


def test_pairdist():
    points = np.array([[2, 3],
                       [1, 1],
                       [2, 2]], dtype=float)

    result = entpy.calc.pairdist(points)
    assert (result == np.array([np.sqrt(5), 1, np.sqrt(2)])).all()