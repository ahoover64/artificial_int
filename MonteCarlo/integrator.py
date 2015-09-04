import random
import sys

if len(sys.argv) > 2:
    lower = sys.argv[1]
    upper = sys.argv[2]
else:
    print "You must enter a lower and upper boud."

# Function to intgerate
f = lambda x: x ** 2
c = 1

'''
Implementation of Monte Carlo Method of finding the Area under the curve
of the specified lambda function
'''

def min_max(f, l, u):
    yend = f(u)
    ybegin = f(l)

i = 0
hits = 0
while i < n:
    x = random.random() * (upper - lower) + lower
    y = random.random() * (ymax - ymin) + ymin
    if f(x,y) <= c:
        hits = hits + 1
    i = i + 1

area = (xmax - xmin) * (ymax - ymin) * 1.0
auc = area * hits / n
print auc
