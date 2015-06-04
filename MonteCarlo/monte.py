import random
import sys

if len(sys.argv) > 1:
    n  = int(sys.argv[1])
else:
    n = 10000 # default dart value
if len(sys.argv) > 2:
    xmin = int(sys.argv[2])
    xmax = int(sys.argv[3])
    ymin = int(sys.argv[4])
    ymax = int(sys.argv[5])
else:
    xmin = -1
    xmax = 1
    ymin = -1
    ymax = 1

f = lambda x, y: x ** 2 + y ** 2
c = 1

'''
Implementation of Monte Carlo Method of finding the Area under the curve
of the specified lambda function
'''

i = 0
hits = 0
while i < n:
    x = random.random() * (xmax - xmin) + xmin
    y = random.random() * (ymax - ymin) + ymin
    if f(x,y) <= c:
        hits = hits + 1
    i = i + 1

area = (xmax - xmin) * (ymax - ymin) * 1.0
auc = area * hits / n
print auc
