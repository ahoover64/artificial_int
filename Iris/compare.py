import sys

#AVERAGES TAKEN FROM OUTPUT OF FIRST 80% OF EACH CLASS
setosa_avg = [5.0375, 3.44, 1.4625, 0.2325]
versi_avg = [6.01, 2.78, 4.3175, 1.35]
virgin_avg = [6.6225, 2.96, 5.6075, 1.99]
averages = [setosa_avg, versi_avg, virgin_avg]

filename = 'iris_data.txt' if len(sys.argv) < 2 else sys.argv[1]
num_start = 0 if len(sys.argv) < 3 else int(sys.argv[2])
num_stop = -1 if len(sys.argv) < 4 else int(sys.argv[3])

file = open(filename, 'r')

#data = []
next_ele = file.readline()
next_ele = file.readline()
data_list = [0,0,0,0]
i = num_start
for x in range(i):
    file.readline()

print "0 -> setosa\n1 -> versicolor\n2 -> virginica"

diff_list = [0,0,0,0]
while next_ele != '' and i != num_stop:
    flower_data = next_ele.split(',')
    species = str(flower_data.pop())[5:-1]
    dist = [0.0,0.0,0.0]
    for j in range(len(flower_data)):
        data_list[j] = float(flower_data[j])
    for j in range(len(averages)):
        for k in range(len(data_list)):
            #dist[j] = dist[j] + ((data_list[k] - averages[j][k]) ** 2) #EUCLID
            #dist[j] = dist[j] + abs((data_list[k] - averages[j][k])) #MANHATTAN
            diff_list[k] = data_list[k] - averages[j][k] #CHEBYCHEV
        dist[j] = max(diff_list) # CHEBYCHEV
    print dist.index(min(dist)), species
    #data.append(copy.deepcopy(data_list))
    next_ele = file.readline()
    i = i + 1
