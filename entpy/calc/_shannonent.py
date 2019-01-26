"""Shannon entropy"""
import numpy as np

def shannonent(data: np.ndarray, units: str = 'bits'):
    r"""Estimate Shannon entropy from data.

    The Shannon entropy is defined as

    .. math::

        H(X) = -\sum_{x \in \mathcal{X}} p(x) \log p(x)

    Where each :math:`x` is a discrete symbol in the support set 
    :math:`\mathcal{X}`. The simple estimator is obtained by calculating
    the relative frequency of each symbol :math:`f(x) = \frac{n(x)}
    {\sum_{x \in \mathcal{X}}n(x)}` and using that as an estimate of the
    probabilities:

    .. math::

        \hat{H}(X) = -\sum_{x \in \mathcal{X}} f(x) \log f(x)
 
    Parameters
    ----------

        data : array_like or iterable
            The data to estimate from. This must be a discrete dtype
            (Shannon entropy does not make sense on floating point
            values, but you can use integers, boolean, or string 
            symbols.)
        units : {"bits", "nats", float}
            Specify the units.
            
            * ``"bits"`` will take the logarithm to base 2
            * ``"nats"`` will use the natual logarithm (base :math:`e`)
            * Some other base (specify as ``float``)

    Returns
    -------

    float
        Estimated entropy

    Examples
    --------

        >>> import entpy.calc
        >>> entpy.calc.shannonent([0, 1] * 20, 'bits')
        1.0
        >>> entpy.calc.shannonent([0, 1] * 20, 'nats')
        0.6931471805599453
        >>> entpy.calc.shannonent([0, 1] * 20, 2)
        1.0
        >>> entpy.calc.shannonent("1234")
        2.0

    """

    data = np.array(data, copy=False).flatten()
    if data.shape[0] == 1:
        # There is only one element in the array. If that element
        # is iterable (e.g. it is a string) assume we want the entropy
        # of the elements
        try:
            iter_data = np.array([x for x in data[0]])
        except TypeError:
            # Couldn't iterate, leave data alone
            pass
        else:
            data = iter_data
    data_dtype = data.dtype
    if np.issubdtype(data_dtype, np.inexact):
        raise TypeError(f"Data type {data_dtype} is not discrete")
    if units not in ('bits', 'nats'):
        try:
            units = np.float(units)
        except (ValueError, TypeError):
            raise ValueError(f"units must be 'bits', 'nats' or a number")
    
    return _shannonent_py(data, units)
    
def _shannonent_py(data, units):
    """Simple numpy implementation"""

    _, counts = np.unique(data, return_counts=True)
    total = float(data.shape[0])
    freq = counts.astype(float) / total

    if units == "bits":
        log_function = np.log2
    elif units == "nats":
        log_function = np.log
    else:
        log_function = lambda x: np.log(x) / np.log(units)

    log_freq = log_function(freq)

    return -np.sum(freq * log_freq)

