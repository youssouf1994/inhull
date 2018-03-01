import numpy as np
from numpy.linalg import norm, det
import time

def zero_point_index(point_cloud):
	for (index, point) in enumerate(point_cloud):
		if np.prod(point == 0) == 1:
			return index
	return -1

def minor_det(points, index):
	assert index < points.shape[0]
	aux_points = np.zeros((points.shape[0]-1, points.shape[0]-1))
	for i in range(points.shape[0]):
		if i < index:
			aux_points[i] = points[i]
		if i > index:
			aux_points[i-1] = points[i]
	return det(aux_points) 

def cross_prod(points):
	cross_prod_dim = points.shape[0]
	dim = points.shape[1]
	assert dim == cross_prod_dim - 1
	cross_prod_value = np.zeros(cross_prod_dim)
	p = 1
	for i in range(cross_prod_dim):
		cross_prod_value[i] = p*minor_det(points, i)
		p = p*(-1) 
	return cross_prod_value

class inhull_2d:
	def __init__(self, point_cloud):
		self.number_of_points = point_cloud.shape[0]
		self.point_cloud = point_cloud
		self.dim = point_cloud.shape[1]
	
	def check (self, point):
		assert len(point) == self.dim
		start_construct_time = time.time()
		u = np.zeros(self.number_of_points)
		
		### Translate all points to zero
		new_point_cloud = self.point_cloud - np.array(point, ndmin = 2)
		
		### Check if zero is an element of the new point_cloud
		end_construct_time = time.time()
		start_check_time = time.time()
		index = zero_point_index (new_point_cloud)
		if index >= 0:
			u[index] = 1.
			return {'__inhull' : True, '__u' : u, 'mTime' : end_construct_time - start_construct_time, 'cTime' : time.time() - start_check_time}
	
		### The angles of the new point_cloud in [0,2pi[
		angles = np.pi + np.arctan2(new_point_cloud[:,1], new_point_cloud[:,0])

		### Sort the angles
		angle_sort_indices = np.argsort(angles, kind='mergesort')

		### Check for all points if zero is in the hull of three points	
		for index in range(self.number_of_points):

			### Take the angle of the current point
			angle = angles[index]

			### Take the angle of the opposite point
			new_angle = angle + np.pi

			### Make sure that the oposite angle is in [0, 2pi[
			if new_angle >= 2*np.pi:
				new_angle -= 2*np.pi

			### Look for the position of the opposite angle in the array of angles
			new_index = np.searchsorted(a = angles, v = new_angle, side = 'left', sorter = angle_sort_indices)
			if new_index < self.number_of_points and angles[new_index] == new_angle:
				u[index] = norm(new_points_cloud[new_index])
				u[new_index] = norm(new_points_cloud[new_index])
				return {'__inhull' : True, '__u' : u / np.sum(u), 'mTime' : end_construct_time - start_construct_time, 'cTime' : time.time() - start_check_time}

			right_index = angle_sort_indices[new_index % self.number_of_points]
			left_index = angle_sort_indices[(new_index - 1) % self.number_of_points]
			uu = cross_prod(new_point_cloud[[index, left_index, right_index]])
			if np.prod(uu >= 0) == 1 and np.sum(uu) > 0:
				u[index] = uu[0]
				u[right_index] = uu[2]
				u[left_index] = uu[1]
				return {'__inhull' : True, '__u' : u / np.sum(u), 'mTime' : end_construct_time - start_construct_time, 'cTime' : time.time() - start_check_time}
			
		return {'__inhull' : False, '__u' : None, 'mTime' : end_construct_time - start_construct_time, 'cTime' : time.time() - start_check_time}
