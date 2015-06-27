import matplotlib.pyplot as plt
from sys import argv, exit

def plot_sequential():
	f = open('seq_vals.txt', 'r')
	x_coordinates = []
	y_coordinates = []
	for line in f:
		if '.' in line:
			y_coordinates.append(float(line))
		else:
			x_coordinates.append(int(line))
	f.close()
	plt.plot(x_coordinates, y_coordinates, 'r-', label="sequential")
	plt.xlabel('Set Size')
	plt.ylabel('Time')
	plt.legend(loc=2)
	plt.show()

def plot_parallel():
	f = open('par4_vals.txt', 'r')
	x_coordinates_p4 = []
	y_coordinates_p4 = []
	for line in f:
		if '.' in line:
			y_coordinates_p4.append(float(line))
		else:
			x_coordinates_p4.append(int(line))
	f.close()

	f = open('par8_vals.txt', 'r')
	x_coordinates_p8 = []
	y_coordinates_p8 = []
	for line in f:
		if '.' in line:
			y_coordinates_p8.append(float(line))
		else:
			x_coordinates_p8.append(int(line))
	f.close()

	f = open('par12_vals.txt', 'r')
	x_coordinates_p12 = []
	y_coordinates_p12 = []
	for line in f:
		if '.' in line:
			y_coordinates_p12.append(float(line))
		else:
			x_coordinates_p12.append(int(line))
	f.close()

	f = open('par16_vals.txt', 'r')
	x_coordinates_p16 = []
	y_coordinates_p16 = []
	for line in f:
		if '.' in line:
			y_coordinates_p16.append(float(line))
		else:
			x_coordinates_p16.append(int(line))
	f.close()

	plt.plot(x_coordinates_p4, y_coordinates_p4, 'b-', label="parallel4")
	plt.plot(x_coordinates_p8, y_coordinates_p8, 'c-', label="parallel8")
	plt.plot(x_coordinates_p12, y_coordinates_p12, 'r-', label="parallel12")
	plt.plot(x_coordinates_p16, y_coordinates_p16, 'm-', label="parallel16")

	plt.xlabel('Set Size')
	plt.ylabel('Time')
	plt.legend(loc=4)
	plt.show()


def plot_both():
	# f = open('seq_vals.txt', 'r')
	# x_coordinates_s = []
	# y_coordinates_s = []
	# for line in f:
	# 	if '.' in line:
	# 		y_coordinates_s.append(float(line))
	# 	else:
	# 		x_coordinates_s.append(int(line))
	# f.close()

	# f = open('par_vals.txt', 'r')
	# x_coordinates_p = []
	# y_coordinates_p = []
	# for line in f:
	# 	if '.' in line:
	# 		y_coordinates_p.append(float(line))
	# 	else:
	# 		x_coordinates_p.append(int(line))
	# f.close()
	# plt.plot(x_coordinates_s, y_coordinates_s, 'r-', label="sequential")
	# plt.plot(x_coordinates_p, y_coordinates_p, 'b-', label="parallel")
	# plt.xlabel('Set Size')
	# plt.ylabel('Time')
	# plt.legend(loc=2)
	f = open('seq_vals.txt', 'r')
	x_coordinates = []
	y_coordinates = []
	for line in f:
		if '.' in line:
			y_coordinates.append(float(line))
		else:
			x_coordinates.append(int(line))
	f.close()

	f = open('par4_vals.txt', 'r')
	x_coordinates_p4 = []
	y_coordinates_p4 = []
	for line in f:
		if '.' in line:
			y_coordinates_p4.append(float(line))
		else:
			x_coordinates_p4.append(int(line))
	f.close()

	f = open('par8_vals.txt', 'r')
	x_coordinates_p8 = []
	y_coordinates_p8 = []
	for line in f:
		if '.' in line:
			y_coordinates_p8.append(float(line))
		else:
			x_coordinates_p8.append(int(line))
	f.close()

	f = open('par12_vals.txt', 'r')
	x_coordinates_p12 = []
	y_coordinates_p12 = []
	for line in f:
		if '.' in line:
			y_coordinates_p12.append(float(line))
		else:
			x_coordinates_p12.append(int(line))
	f.close()

	f = open('par16_vals.txt', 'r')
	x_coordinates_p16 = []
	y_coordinates_p16 = []
	for line in f:
		if '.' in line:
			y_coordinates_p16.append(float(line))
		else:
			x_coordinates_p16.append(int(line))
	f.close()

	plt.plot(x_coordinates, y_coordinates, 'y-', label="sequential")
	plt.plot(x_coordinates_p4, y_coordinates_p4, 'b-', label="parallel4")
	plt.plot(x_coordinates_p8, y_coordinates_p8, 'c-', label="parallel8")
	plt.plot(x_coordinates_p12, y_coordinates_p12, 'r-', label="parallel12")
	plt.plot(x_coordinates_p16, y_coordinates_p16, 'm-', label="parallel16")

	plt.xlabel('Set Size')
	plt.ylabel('Time')
	plt.legend(loc=5)
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
