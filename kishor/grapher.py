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
	f.close()
	plt.plot(x_coordinates, y_coordinates, 'r-', label="sequential")
	plt.xlabel('Window Dimension')
	plt.ylabel('Time')
	plt.legend(loc=2)
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
	f.close()
	plt.plot(x_coordinates, y_coordinates, 'b-', label="parallel")
	plt.xlabel('Window Dimension')
	plt.ylabel('Time')
	plt.legend(loc=2)
	plt.show()

def plot_both():
	f = open('main_vals.txt', 'r')
	x_coordinates_s = []
	y_coordinates_s = []
	for line in f:
		if '.' in line:
			y_coordinates_s.append(float(line))
		else:
			x_coordinates_s.append(int(line))
	f.close()

	f = open('parallel_vals.txt', 'r')
	x_coordinates_p = []
	y_coordinates_p = []
	for line in f:
		if '.' in line:
			y_coordinates_p.append(float(line))
		else:
			x_coordinates_p.append(int(line))
	f.close()
	plt.plot(x_coordinates_s, y_coordinates_s, 'r-', label="sequential")
	plt.plot(x_coordinates_p, y_coordinates_p, 'b-', label="parallel")
	plt.xlabel('Window Dimension')
	plt.ylabel('Time')
	plt.legend(loc=2)
	plt.show()

try:
	choice = argv[1]
except:
	print 'Usage: python grapher.py [seq|par|both]'
	exit(0)

if choice == 'seq':
	plot_sequential()
elif choice == 'par':
	plot_parallel()
elif choice == 'both':
	plot_both()
else:
	print 'Usage: python grapher.py [seq|par|both]'
