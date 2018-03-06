import numpy as np
from inhull import inhull_2d
from numpy.linalg import norm

class inhull_optim:
	def __init__(self, point_cloud):
		self.number_of_points = point_cloud.shape[0]
		self.point_cloud = point_cloud
		self.dim = point_cloud.shape[1]
	def check (self):
		restricted_point_cloud = np.zeros((2*self.dim, self.dim))
		for i in range(self.number_of_points):
			self.point_cloud[i] = self.point_cloud[i] / norm(self.point_cloud[i])
		for i in range(2*self.dim):
			restricted_point_cloud[i] = self.point_cloud[0]
		for i in range(self.number_of_points):
			for j in range(self.dim):
				if(self.point_cloud[i][j] > restricted_point_cloud[j][j]):
					restricted_point_cloud[j] = self.point_cloud[i]
			for j in range(self.dim):
				if(self.point_cloud[i][j] < restricted_point_cloud[j+self.dim][j]):
					restricted_point_cloud[j+self.dim] = self.point_cloud[i]

		res = inhull_2d(restricted_point_cloud).check()
		if not res['__inhull']:
			print(restricted_point_cloud)

		return res
