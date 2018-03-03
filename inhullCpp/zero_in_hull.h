#include "point.h"
#include "time.h"
#include "hull_solution.h"
#include "types.h"

#ifndef ZERO_IN_HULL_H
#define ZERO_IN_HULL_H

class ZeroInHull
{
public:
	Points points;
	PointCloud pointCloud;
	Time time;
	ZeroInHull () : time(0) {};
	ZeroInHull (Points points0) : points(points0), time(0)
	{
		int index = 0;
		Time t = clock();
		for (Points::iterator it = points0.begin(); it != points0.end(); ++it)
		{
			pointCloud.insert(pair<Point2D, int>(*it, index));
			index++;
		}
		time += clock() - t;
	};
	~ZeroInHull () {};
	static pair<Point2D, int> left (Point2D& p, PointCloud pcloud)
	{
		PointCloud::iterator it = pcloud.lower_bound(p);
		if (it == pcloud.begin())
		{
			if (it->first == p)
			{
				return *it;
			}
			return *(pcloud.rbegin());
		}
		it--;
		return *it;
	};
	static pair<Point2D, int> right (Point2D& p, PointCloud pcloud)
	{
		PointCloud::iterator it = pcloud.upper_bound(p);
		if (it == pcloud.end())
			return *(pcloud.begin());
		return *it;
	};
	Solution check ()
	{
		Time t = clock();
		for (PointCloud::iterator it = pointCloud.begin(); it != pointCloud.end(); ++it)
		{
			
			Point2D point = it->first;
			int index = it->second;
			Point2D oppPoint(-point.x, -point.y);
			
			pair<Point2D, int> leftPair = left(oppPoint, pointCloud);
			Point2D leftPoint = leftPair.first;
			int leftIndex = leftPair.second;

			pair<Point2D, int> rightPair = right(oppPoint, pointCloud);
			Point2D rightPoint = rightPair.first;
			int rightIndex = rightPair.second;
			
			Point3D crossProd = Point2D::crossProduct (point, leftPoint, rightPoint);
			if (crossProd > 0)
			{
				Coeffs* u0 = new Coeffs();
				double sum = crossProd.sum ();
				crossProd = crossProd / sum;
				(*u0).push_back(Coeff(index, crossProd.x));
				(*u0).push_back(Coeff(leftIndex, crossProd.y));
				(*u0).push_back(Coeff(rightIndex, crossProd.z));
				return Solution (FEASIBLE, u0, clock() - t + time);
			}
		}
		return Solution (INFEASIBLE, NULL, clock() - t + time);
	};
	
};

#endif
