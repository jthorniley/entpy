from pytest import approx, mark, raises

from entpy.calc import shannonent


@mark.parametrize('input,entropy', [
    (([],), 0.0),
    ((1,), 0.0),
    (([1],), 0.0),
    (([1, 0],), 1.0),
    (([1, 0] * 20,), 1.0),
    (([1, 0] * 20, 'bits'), 1.0),
    (([1, 0] * 20, 2), 1.0),
    (([1, 0] * 20, 'nats'), 0.6931471805599453),
    (([1, 2, 3, 4],), 2.0),
    (("1234",), 2.0),
])
def test_shannonent(input, entropy):
    assert entropy == approx(shannonent(*input))


def test_float_input_raises():
    with raises(TypeError):
        shannonent([1.0, 2.0])


@mark.parametrize('bad_input', (None, -1, 'foo'))
def test_bad_units_raises(bad_input):
    with raises(ValueError):
        shannonent([1,2,3], bad_input)