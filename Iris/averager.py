import sys
import copy

filename = 'iris_data.txt' if len(sys.argv) < 2 else sys.argv[1]
num_read = 50 if len(sys.argv) < 3 else int(sys.argv[2])

file = open(filename, 'r')

data = []
next_ele = file.readline()
next_ele = file.readline()
data_list = [0,0,0,0]
i = 0

while next_ele != '' and i < num_read:
    flower_data = next_ele.split(',')
    species = str(flower_data.pop())
    for j in range(len(flower_data)):
        data_list[j] = float(flower_data[j])
    data.append(copy.deepcopy(data_list))
    next_ele = file.readline()
    i = i + 1

sums = [0.0,0.0,0.0,0.0]
averages = [0.0,0.0,0.0,0.0]
for flower in data:
    for i in range(len(flower)):
        sums[i] = sums[i] + flower[i]
for i in range(len(sums)):
    averages[i] = sums[i] / len(data)
print averages
