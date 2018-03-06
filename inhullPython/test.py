import numpy as np
from numpy.linalg import norm

#####################################
#
# LP function to solve the problem
#
#####################################
from cvxopt import matrix, solvers

def zero_in_hull (points):
	m = points.shape[0]
	n = points.shape[1]
	G = matrix (-np.diag(np.ones(m)))
	h = matrix (np.zeros((m,1)))
	A = matrix (np.concatenate((points, np.ones((m,1))), axis=1).T)
	b = matrix (np.concatenate((np.zeros((n,1)), np.ones((1,1))), axis=0))
	c = matrix (np.zeros(m))
	sol = solvers.lp(c = c, G = G, h = h, A = A, b = b)
	if sol['status'] == 'primal infeasible':
		return False
	else:
		return True
	


###################################
#
# Create cloud of points
#
###################################


n = int(raw_input())
m = int(raw_input())

point_cloud = np.zeros((1,n))
for i in range(m):
	new_point = np.array([float(i) for i in raw_input().split(" ")], ndmin = 2)
	point_cloud = np.concatenate((point_cloud, new_point), axis = 0)

point_cloud = point_cloud[1:]

extrem_points = np.zeros((2*n, n))
for i in range(m):
	point_cloud[i] = point_cloud[i] / norm(point_cloud[i])
for i in range(2*n):
	extrem_points[i] = point_cloud[0]

for i in range(m):
	for j in range(n):
		if(point_cloud[i][j] > extrem_points[j][j]):
			extrem_points[j] = point_cloud[i]
	for j in range(n):
		if(point_cloud[i][j] < extrem_points[j+n][j]):
			extrem_points[j+n] = point_cloud[i]

print zero_in_hull(point_cloud)
print zero_in_hull(extrem_points)

