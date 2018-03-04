
import numpy as np
from numpy.random import randn

def random_points(n, dim):
	return randn(n, dim)
import sys

if __name__ == "__main__":
	if len(sys.argv) < 2:
		print ("Please add an argument for the number of points")
		sys.exit(0)
	n = int(sys.argv[1])
	for i in range(n):
		p = randn(2)
		print(str(p[0]) + " " + str(p[1]))

