#include <iostream>
#include <fstream>
#include <string>
#include "zero_in_hull.h"
#include "point.h"
#include "types.h"
#include "hull_solution.h"

using namespace std;

Points pointsFromFile (string filename) 
{
	Points points;
	string line;
	ifstream f(filename);
	if (f.is_open())
	{
		while ( getline (f,line) )
		{
			points.push_back(Point2D(line));
		}
		f.close();
	}
	return points;
}
int main ()
{
	string filename = "../in/0.in";
	Points points = pointsFromFile (filename);
	ZeroInHull zeroInHull(points);
	Solution solution = zeroInHull.check();
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
	}
	else
		cout << "0 is not in the convexhull" << endl;
	return 0;
}
