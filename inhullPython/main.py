from inhull import inhull_2d as ih2
# from inhull_LP import inhull_LP as ihLP
from inhull_optim import inhull_optim as ihO

import numpy as np

def create_point_cloud (filename):
	f = open(filename, 'r')
	n = int(f.readline())
	m = int(f.readline())
	point_cloud = np.zeros((1,n))
	for i in range(m):
		new_point = np.array([float(i) for i in f.readline().split(" ")], ndmin = 2)
		point_cloud = np.concatenate((point_cloud, new_point), axis = 0)
	return point_cloud[1:]

from numpy.random import randn, poisson

def random_points(n, dim):
	return randn(n, dim)

def random_number_of_points(dim):
	return dim + poisson(lam = 100)

# import sys

# if len(sys.argv) < 2:
#	print ("Please make sure you add the filename")
#	sys.exit(0)

# points = create_point_cloud(sys.argv[1]) 

# print(points)

N = 10
dim = 2
n = 100

times_ih2 = []
times_LP = []

import matplotlib.pyplot as plt
import os

if not os.path.exists("figures/"):
    os.makedirs("figures/")


for _ in range(N):
	ndim = random_number_of_points(dim)
	times_ih2 = []
	times_LP = []
	plt.figure()
	for __ in range(n):
		points = random_points(ndim, dim)
		ih_instance = ih2 (points)
		res_ih2 = ih_instance.check()
		times_ih2.append(res_ih2['cTime'])
		# ih_instance = ihLP(points)
		# res_LP = ih_instance.check()
		# times_LP.append(res_LP['cTime'])
		ih_instance = ihO(points)
		res_ihO = ih_instance.check()
	        # print(str(res_ih2['__inhull'] == res_LP['__inhull']))
		print (str(res_ihO['__inhull']) + " " + str(res_ih2['__inhull']))
	times_ih2 = np.array(times_ih2)
	times_LP = np.array(times_LP)
	# plt.plot(range(n), times_ih2 / times_LP)
	# plt.savefig("figures/fig" + str(_))


