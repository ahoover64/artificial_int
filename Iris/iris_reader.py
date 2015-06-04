import sys

filename = 'iris_data.txt' if len(sys.argv) < 2 else sys.argv[1]

file = open(filename, 'r')

flowers = {'Iris-setosa\n': [], 'Iris-versicolor\n': [], 'Iris-virginica\n': []}
species_list = []
next_ele = file.readline()
next_ele = file.readline()
data_list = [0,0,0,0]
i = 0

while next_ele != '' and i < 40:
    flower_data = next_ele.split(',')
    species = str(flower_data.pop())
    for j in range(len(flower_data)):
        data_list[j] = float(flower_data[j])
    flowers[species].append(data_list)
    next_ele = str(file.readline())
    i = i + 1

print flowers
sums = [0.0,0.0,0.0,0.0]
averages = {}
for key, val in flowers:
    averages[key] = [0.0, 0.0, 0.0, 0.0]
    for flower in val:
        for i in range(len(flower)):
            sums[i] += flower[i]
    for i in range(4):
        averages[key][i] = sums[i] / len(val)

print averages
