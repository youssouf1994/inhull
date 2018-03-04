#include "point.h"
#include "time.h"
#include "hull_solution.h"
#include "types.h"
#include "math.h"

#ifndef ZERO_IN_HULL_H
#define ZERO_IN_HULL_H

# define M_PI           3.14159265358979323846


class ZeroInHull;
class ZeroInHullOptimized;

class Point2DComparator
{
public:
	Point2D point;
	double ori;
	Point2DComparator(Point2D p) : point(p) 
	{
		if (p.x == 0 && p.y == 0) 
		{
			ori = 2*M_PI;
		}
		else
		{
			ori = atan2(p.y, p.x); 
		}
	};
	~Point2DComparator() {};
	double orientation (const Point2D& p)
	{
		if (p.x == 0 && p.y == 0) 
		{
			return 2*M_PI;
		}
		else
		{
			double o = atan2(p.y, p.x) - ori;
			if (ori >= 0)
				return (o >= -M_PI)? o : o + 2*M_PI;
			else
				return (o <= M_PI) ? o : o - 2*M_PI;
		}
	}
	bool isUpSide (const Point2D& p)
	{
		return (orientation(p) >= 0);
	}

	int compare(const Point2D& p, const Point2D& q)
	{
		double pori = orientation(p);
		double qori = orientation(q);
		return (pori < qori)? -1 : ((pori > qori)? 1 : 0);
	}
};

class ZeroInHull
{
public:
	Points points;
	ZeroInHull () : points() {};
	ZeroInHull (Points points0) : points(points0) {};
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
		int index = 0;
		Time t = clock();
		PointCloud pointCloud;
		for (Points::iterator it = points.begin(); it != points.end(); ++it)
		{
			pointCloud.insert(pair<Point2D, int>(*it, index));
			index++;
		}
		PointCloud::iterator it = pointCloud.begin();		
		
		Point2D point = points[0];
		index = 0;
		Point2D oppPoint(-point.x, -point.y);
		
		pair<Point2D, int> leftPair = left(oppPoint, pointCloud);
		Point2D leftPoint = leftPair.first;
		int leftIndex = leftPair.second;

		pair<Point2D, int> rightPair = right(oppPoint, pointCloud);
		Point2D rightPoint = rightPair.first;
		int rightIndex = rightPair.second;
		
		Point3D crossProd = Point2D::crossProduct (point, leftPoint, rightPoint);
		cout << point << leftPoint << rightPoint << endl;
		cout << crossProd << endl;
		if (crossProd > 0)
		{
			Coeffs* u0 = new Coeffs();
			double sum = crossProd.sum ();
			crossProd = crossProd / sum;
			(*u0).push_back(Coeff(index, crossProd.x));
			(*u0).push_back(Coeff(leftIndex, crossProd.y));
			(*u0).push_back(Coeff(rightIndex, crossProd.z));
			return Solution (FEASIBLE, u0, clock() - t);
		}
		return Solution (INFEASIBLE, NULL, clock() - t);
	};
	
};

class ZeroInHullOptimized
{
public:
	Points points;
	ZeroInHullOptimized () : points() {};
	ZeroInHullOptimized (Points points0) : points(points0) {};
	~ZeroInHullOptimized () {};
	Solution check ()
	{
		int leftIndex = 0;
		Point2D leftPoint = points[0];
		int rightIndex = 0;
		Point2D rightPoint = points[0];
		int index = 0;
		Point2D point = points[0];
		Point2DComparator pointComparator(point);

		Time t = clock();
		for (Points::iterator it = points.begin(); it != points.end(); ++it)
		{
			if (pointComparator.isUpSide(*it))
			{
				if (pointComparator.compare(leftPoint, *it) == -1)
				{
					leftIndex = index;
					leftPoint = *it;
				}
			}
			else
			{
				if (pointComparator.compare(rightPoint, *it) == 1)
				{
					rightIndex = index;
					rightPoint = *it;
				} 
			}
			index++;
		}
		index = 0;
		Point3D crossProd = Point2D::crossProduct (point, leftPoint, rightPoint);
		if (crossProd > 0)
		{
			Coeffs* u0 = new Coeffs();
			double sum = crossProd.sum ();
			crossProd = crossProd / sum;
			(*u0).push_back(Coeff(index, crossProd.x));
			(*u0).push_back(Coeff(leftIndex, crossProd.y));
			(*u0).push_back(Coeff(rightIndex, crossProd.z));
			return Solution (FEASIBLE, u0, clock() - t);
		}
		return Solution (INFEASIBLE, NULL, clock() - t);
	};
};

#endif
