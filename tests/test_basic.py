from edit_distance_tools import weighted_levenshtein


def test_main():
    s1 = [1, 5, 3]
    s2 = [1, 2, 3, 4]

    w1 = [0.1, 0.2, 0.3]
    w2 = [0.1, 0.25, 0.4, 1.0]

    x = weighted_levenshtein(s1, s2, w1, w2, 3, 4)
    assert x == 1.45
