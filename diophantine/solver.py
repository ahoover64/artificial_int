'''
Pell's Equation: x^2 - D * y^2 = 1
An implementation of Pell's Equation solver using differenet solving methods
1. Brute Force
2. Continued Fraction
'''

import thread
import time
import sys
import math

D = 7
pell = lambda x, y: x**2 - D * y**2

def solve_brute_force():
    x = 0
    while(True):
        x = x + 1
        for j in xrange(x):
            y = j + 1
            if pell(x,y) == 1:
                return x, y
            if pell(y,x) == 1:
                return y, x

def solve_continued_fraction():
    x = f = math.sqrt(D)
    a0 = an = math.floor(x)
    n = 0
    # INITIALIZE P0
    p0 = pn = a0
    pold = 1
    # INITIALIZE Q0
    q0 = qn = 1
    qold = 0
    while an != 2*a0:
        prev, an, f = an, math.floor(1 / (f - an)), 1 / (f - an)
        pn, pold = an * pn + pold, pn
        qn, qold = an * qn + qold, qn
        r, n = n, n + 1
    ar = prev
    if r % 2 == 1:
        return pold, qold
    else:
        while n < 2 * r + 2:
            prev, an, f = an, math.floor(1 / (f - an)), 1 / (f - an)
            pn, pold = an * pn + pold, pn
            qn, qold = an * qn + qold, qn
            n = n + 1
        return pold, qold

def is_perfect_square(n):
    if n < 0:
        return False
    return math.floor(math.sqrt(n)) == math.sqrt(n)


D = 2
max_sol = 0
start = time.time()
while D <= 40:
    loc_max = max(solve_brute_force())
    if loc_max > max_sol:
        max_sol = loc_max
    #print solve_brute_force()
    D = D + 1
    if is_perfect_square(D):
        D = D + 1
print max_sol
end_bf = time.time()
print end_bf - start


start_cont_frac = time.time()
D = 2
max_sol = 0
while D <= 40:
    loc_max = max(solve_continued_fraction())
    if loc_max > max_sol:
        max_sol = loc_max
    #print solve_continued_fraction()
    D = D + 1
    if is_perfect_square(D):
        D = D + 1
print max_sol
end_cont_frac = time.time()
print end_cont_frac - start_cont_frac
