import sys
import random
import math
import time
import sympy

def elipit_func(x, y, p, a, b):
    return (y ** 2) % p == ((x ** 3) + (a % p) * x + (b % p)) % p

def find_points(p, a, b):
    points = []
    for x in range(p):
        for y in range(p):
            if elipit_func(x, y, p, a, b):
                points.append((x, y))
    return points

def ABtest(a, b):
    if 4 * a ** 3 + 27 * b ** 2 == 0:
        print("Fatal error", file=sys.stderr)
        quit()

def test_p(p):
    if not(sympy.isprime(p)):
        print("Fatal error", file=sys.stderr)
        quit()

def list_to_float(lst):
    for i in range(len(lst)):
        lst[i] = float(lst[i])

def extended_euclidean_algorithm(a, b):
    s, old_s = 0, 1
    t, old_t = 1, 0
    r, old_r = b, a
    while r != 0:
        quotient = old_r // r
        old_r, r = r, old_r - quotient * r
        old_s, s = s, old_s - quotient * s
        old_t, t = t, old_t - quotient * t
    return old_r, old_s, old_t

def inverse_of(n, p):
    gcd, x, y = extended_euclidean_algorithm(n, p)
    assert (n * x + p * y) % p == gcd
    if gcd != 1:
        raise ValueError(
            '{} не имеет мультпликативную инверсию'
            'Mod {}'.format(n, p))
    else:
        return x % p

def add_points(p1, p2, p, a):
    x1, y1 = p1[0], p1[1]
    x2, y2 = p2[0], p2[1]
    if p1 == (0, 0):
        return p2
    elif p2 == (0, 0):
        return p1
    elif x1 == x2 and y1 != y2:
        return (0, 0)
    if p1 == p2:
        m = ((3 * x1 ** 2 + (a % p)) * inverse_of(2 * y1, p)) % p
    else:
        m = ((y1 - y2) * inverse_of(x1 - x2, p)) % p
    x3 = (m ** 2 - x1 - x2) % p
    y3 = (y1 + m * (x3 - x1)) % p
    return [x3, -y3 % p]

def point_order(point, p, a):
    i = 1
    new_point = add_points(point, point, p, a)
    while new_point != (0, 0):
        new_point = add_points(new_point, point, p, a)
        i += 1
    return i

def main():
    elipit = input("Введите значения коэффициентов a и b: ").split()
    p = int(input("Введите коэффициент p эллиптической кривой: "))
    test_p(p)
    list_to_float(elipit)
    a, b = elipit
    ABtest(a, b)
    start = time.time()
    points = find_points(p, a, b)
    point = random.choice(points)
    order = point_order(point, p, a)
    print("Порядок рандомной точки: {0} -> {1}".format(point, order))
    print("Время: {0}".format(time.time() - start))

if __name__ == "__main__":
    main()