#include <iostream>
#include <fstream>
#include <string>
#include "zero_in_hull.h"
#include "point.h"
#include "types.h"
#include "hull_solution.h"

using namespace std;

/*Points pointsFromFile (istream f) 
{
	Points points;
	string line;
	while ( getline (f,line) )
	{
		points.push_back(Point2D(line));
	}
	return points;
}*/
int main ()
{
	// string filename = "../in/1.in";
	
	// Points points = pointsFromFile (cin);
	Points points;
	string line;
	while ( getline (cin,line) )
	{
		points.push_back(Point2D(line));
	}
	ZeroInHull zeroInHull(points);
	Solution solution = zeroInHull.check();
	Point2D c(0,0);
	cout << "Execution time : " << (((float)solution.time)/CLOCKS_PER_SEC) << "s" << endl;
	if (solution.status == FEASIBLE)
	{	
		Coeffs u = *(solution.u);
		cout << "0 is in the convexhull and u = (";
		for (int index = 0; index < points.size(); index++)
		{
			bool zero = false;
			for (Coeffs::iterator it = u.begin(); it != u.end(); ++it)
			{
				if(index == it->first)
				{
					c = c + ((it->second)*points[index]);
					cout << it->second;
					zero = true;
				}
			}
			if (!zero)
			{
				cout << "0";
			}
			if (index != points.size()-1)
			{
				cout << ", ";
			}
			else
			{
				cout << ")" << endl;
			}
		}
		cout << c << endl;
	}
	else
		cout << "0 is not in the convexhull" << endl;
	return 0;
}
