from inhull import inhull_2d as ih2

import numpy as np
def create_point_cloud (filename):
	f = open(filename, 'r')
	n = int(f.readline())
	m = int(f.readline())
	point_cloud = np.zeros((1,n))
	for i in range(m):
		new_point = np.array(map(float, f.readline().split(" ")), ndmin = 2)
		point_cloud = np.concatenate((point_cloud, new_point), axis = 0)
	return point_cloud[1:]


import sys

if len(sys.argv) < 2:
	print ("Please make sure you add the filename")
	sys.exit(0)

ih2_instance = ih2 (create_point_cloud(sys.argv[1]))

print ih2_instance.point_cloud

res = ih2_instance.check(np.zeros(ih2_instance.dim))

print res['__inhull'], res['__u']

