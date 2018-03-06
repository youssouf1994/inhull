
import numpy as np
from numpy.random import randn

def random_points(n, dim):
	return randn(n, dim)
import sys

if __name__ == "__main__":
	if len(sys.argv) < 3:
		print ("Please add an argument for the number of points or the dim argument")
		sys.exit(0)
	dim = int(sys.argv[1])
	print dim
	n = int(sys.argv[2])
	print n
	for i in range(n):
		p = randn(dim)
		out = ""
		for i in range (dim):
			out += str(p[i])
			if (i < dim - 1):
				out += " " 
		print(out)

