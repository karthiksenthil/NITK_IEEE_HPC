import matplotlib.pyplot as plt
from sys import argv, exit

def plot_sequential():
	f = open('main_vals.txt', 'r')
	x_coordinates = []
	y_coordinates = []
	for line in f:
		if '.' in line:
			y_coordinates.append(float(line))
		else:
			x_coordinates.append(int(line))
	plt.plot(x_coordinates, y_coordinates, 'r-')
	plt.xlabel('Window Dimension')
	plt.ylabel('Time')
	plt.show()

def plot_parallel():
	f = open('parallel_vals.txt', 'r')
	x_coordinates = []
	y_coordinates = []
	for line in f:
		if '.' in line:
			y_coordinates.append(float(line))
		else:
			x_coordinates.append(int(line))
	plt.plot(x_coordinates, y_coordinates, 'b-')
	plt.xlabel('Window Dimension')
	plt.ylabel('Time')
	plt.show()

try:
	choice = argv[1]
except:
	print 'Usage: python grapher.py [seq|par]'
	exit(0)

if choice == 'seq':
	plot_sequential()
elif choice == 'par':
	plot_parallel()
else:
	print 'Usage: python grapher.py [seq|par]'