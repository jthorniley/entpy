"""Shannon entropy"""
import numpy as np

def shannonent(data: np.ndarray, units: str = 'bits'):
    r"""Estimate Shannon entropy from data.

    The Shannon entropy is defined as

        $ H(X) = -\sum_{x \in \mathcal{X}} p(x) \log p(x) $

    Where each $x$ is a discrete symbol in the support set 
    $\mathcal{X}$. The simple estimator is obtained by calculating the
    relative frequency of each symbol 
    $f(x) = \frac{n(x)}{\sum_{x \in \mathcal{X}}n(x)}$ and using that
    as an estimate of the probabilities:

        $ \hat{H}(X) = -\sum_{x \in \mathcal{X}} f(x) \log f(x) $
    
    Parameters
    ----------

        data : array_like
            The data to estimate from. This must be a discrete dtype
            (Shannon entropy does not make sense on floating point
            values, but you can use integers, boolean, or string 
            symbols.)
        units : {"bits", "nats", float}
            Specify the units.
            * "bits" will take the logarithm to base 2
            * "nats" will use the natual logarithm (base $e$)
            * Some other base (specify as float)

    Returns
    -------

    float
        Estimated entropy

    """

    data = np.array(data, copy=False).flatten()
    data_dtype = data.dtype
    if np.issubdtype(data_dtype, np.inexact):
        raise TypeError(f"Data type {data_dtype} is not discrete")
    
    return _shannonent_py(data, units)
    
def _shannonent_py(data, units):
    """Simple numpy implementation"""

    symbols, counts = np.unique(data, return_counts=True)
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

