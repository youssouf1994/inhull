
import numpy as np
import time
from docplex.mp.model import Model
import cplex

class inhull_LP:
	def __init__(self, point_cloud):
		self.point_cloud = point_cloud
		self.number_of_points = point_cloud.shape[0]
		self.dim = point_cloud.shape[1]
	
	def check(self, point, stream = None):
		### Constructing a model
		start_construct_time = time.time()
		new_point_cloud = self.point_cloud - np.array(point, ndmin=2)
		#### model = Model()
		#### u = model.continuous_var_list(self.number_of_points, lb = 0, ub = 1, name='u')
		#### for i in range(self.dim):
		####	model.add_constraint(model.sum(u[j] * new_point_cloud[j][i] for j in range(self.number_of_points)) == 0)
		#### model.add_constraint(model.sum(u[j] for j in range(self.number_of_points)) == 1)
		#### model.maximize(0)
		c = cplex.Cplex()
		c.set_log_stream(stream)
		c.set_results_stream(stream)
		obj = [0]*self.number_of_points
		lb = [0]*self.number_of_points
		names = ['u_' + str(index) for index in range(self.number_of_points)] 
		c.variables.add(obj = obj, lb = lb, names = names)
		
		orth_constraints = [[range(self.number_of_points), [new_point_cloud[i][j] for i in range(self.number_of_points)]] for j in range(self.dim)]
		orth_rhs = [0]*self.dim
		orth_senses = ["E"]*self.dim
		orth_names = ["o_" + str(index) for index in range(self.dim)]
		c.linear_constraints.add(lin_expr = orth_constraints, senses = orth_senses, rhs = orth_rhs, names = orth_names)
		
		conv_constraints = [[range(self.number_of_points),[1]*self.number_of_points]]
		conv_rhs = [1]
		conv_senses = ["E"]
		conv_names = ["c"]
		c.linear_constraints.add(lin_expr = conv_constraints, senses = conv_senses, rhs = conv_rhs, names = conv_names)
		end_construct_time = time.time()
		start_check_time = time.time()
		c.solve()
		end_check_time = time.time()
		if c.solution.get_status() != 1:
			return {'__inhull' : False, '__u' : None, 'mTime' : end_construct_time - start_construct_time, 'cTime' : end_check_time - start_check_time}
		else:
			return {'__inhull' : True, '__u' : np.array(c.solution.get_values()), 'mTime' : end_construct_time - start_construct_time, 'cTime' : end_check_time - start_check_time}
