
func = lambda x : x ** 2
upper_bound = 5
lower_bound = 0
difference = upper_bound - lower_bound

resolution = 5 #increase for more accurate results

delta_x = float(difference / resolution)
left_sum = 0
right_sum = 0

for i in range(resolution):
    x_i = (i * delta_x) + lower_bound
    x_next = ((i + 1) * delta_x) + lower_bound
    left_sum = left_sum + func(x_i) * delta_x
    right_sum = right_sum + func(x_next) * delta_x

print "Left Reimann Sum: ", left_sum
print "Right Reimann Sum: ", right_sum
