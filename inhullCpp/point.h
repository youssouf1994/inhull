#include "math.h"
#include <iostream>
#include <string>

#ifndef POINT_H
#define POINT_H

using namespace std;

class Point2D;

class Point3D
{
public:
	double x;
	double y;
	double z;
	Point3D (double x0, double y0, double z0) : x(x0), y(y0), z(z0) {};
	~Point3D () {};
	double sum ()
	{
		return (x + y + z);
	}
	friend bool operator >(const Point3D& p, const double d)
	{
		return (p.x >= d && p.y >= d && p.z >= d) && (p.x + p.y + p.z > d);
	};
	friend Point3D operator /(const Point3D& p, const double d)
	{
		return Point3D(p.x / d, p.y / d, p.z / d);
	};
	friend ostream& operator<<(ostream& output,const Point3D& p)
	{
		output<<"("<<p.x<<","<<p.y<<","<<p.z<<")";
		return output;
	};
};

class Point2D
{
public:
	double x;
	double y;
	Point2D (double x0, double y0) : x(x0), y(y0) {};
	Point2D (string line)
	{
		size_t found = line.find(" ");
		string xstring = line.substr(0, found);
		string ystring = line.substr(found + 1);
		x = stod(xstring);
		y = stod(ystring);
	};
	~Point2D () {};
	friend bool operator== (const Point2D& p, const Point2D& q)
	{
		if ((p.x == 0 && p.y == 0) || (q.x == 0 && q.y == 0))
			return (p.x == q.x) && (p.y == q.y);
		double pOrientation = atan2(p.y, p.x);
		double qOrientation = atan2(q.y, q.x);

		return (pOrientation == qOrientation);
	};
	friend bool operator< (const Point2D& p, const Point2D& q)
	{
		if (p.x == 0 && p.y == 0)
			return false;
		if (q.x == 0 && q.y == 0)
			return true;
		double pOrientation = atan2(p.y, p.x);
		double qOrientation = atan2(q.y, q.x);

		return (pOrientation < qOrientation);
	};
	friend Point2D operator+ (const Point2D& p, const Point2D& q)
	{
		return Point2D(p.x + q.x, p.y + q.y);
	};
	friend Point2D operator* (const double d, const Point2D& p)
	{
		return Point2D(d*p.x, d*p.y);
	};
	
	friend ostream& operator<<(ostream& output,const Point2D& p)
	{
		output<<"("<<p.x<<","<<p.y<<")";
		return output;
	};
	static Point3D crossProduct (const Point2D& p, const Point2D& q, const Point2D& r)
	{
		double x = (q.x*r.y - r.x*q.y);
		double y = (r.x*p.y - p.x*r.y);
		double z = (p.x*q.y - q.x*p.y);
		return Point3D(x, y, z);
	};
};

#endif
