import numpy as np

from . import onedca


def sierpinski(n: int) -> np.ndarray:
    """Generate a Sierpinski triangle.

    This is a shortcut to generate a Sierpinski triangle using CA
    rule 90 as the generating method.

    :param n: (int) Number of rows in the generated data (there will be
              twice as many columns). To get a neat triangle, use 2
              raised to an integer (2, 4, 8, 16, 32 etc) here.
    :return: (ndarray[uint8]) Image of a sierpinski triangle. The array
             size will be ``n x n*2+1``.
    """
    triangle = np.zeros((n, n*2+1), dtype=np.uint8)
    # Set a single entry (the top of the triangle) in the middle
    # of the first row.
    triangle[0, n] = 1

    onedca.onedca(triangle, onedca.rule_number_lookup_table(90))

    return triangle
