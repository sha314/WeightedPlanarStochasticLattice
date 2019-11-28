# Given the list of boxes, this script can plot all boxes in a graph


import numpy as np
# import seaborn as sns
import matplotlib.pyplot as plt

# sns.set()

filename="WPSL_1000_boxes.txt"

fig, ax = plt.subplots()
def plot_box(box):
	# print(box)
	x0,y0=box[0]
	x1,y1=box[1]
	y = np.linspace(y0, y1, 4)
	plt.plot(x0*np.ones(4), y)
	plt.plot(x1*np.ones(4), y)
	x = np.linspace(x0, x1, 4)
	plt.plot(x, y0*np.ones(4))
	plt.plot(x, y1*np.ones(4))
	pass

def test():
	limit=[0,1]
	boxes=[[[0,0],[0.4,0.4]], [[0.4,0],[1,0.4]], [[0.4,0.4],[1,1]], [[0, 0.4],[0.4, 1]]]


	plot_box(boxes[0])
	plot_box(boxes[1])
	plot_box(boxes[2])
	plot_box(boxes[3])

	plt.show()
	pass

def get_box(line):
	box = []
	for point in line.split():
		a = point[1:-1].split(',')
		result = list(map(lambda i : float(i), a))
		# print(result)
		box.append(result)
		pass

	return box


def plot_from_file(filename):
	with open(filename) as file:
		line = file.readline()
		while line:
			if(line[0] == '#'):
				line = file.readline()
				continue
			box = get_box(line)
			
			plot_box(box)
			line = file.readline()
			pass
		pass
	pass

plot_from_file(filename)
plt.show()