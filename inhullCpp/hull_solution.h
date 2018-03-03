#include "point.h"
#include "types.h"

#ifndef HULL_SOLUTION_H
#define HULL_SOLUTION_H

class Solution
{
public:
	Status status;
	Coeffs* u;
	Time time;
	Solution (Status s, Coeffs* u0, Time t)
	{
		status = s;
		u = u0;
		time = t;
	};
	~Solution () 
	{
		delete u;
	};
};

#endif
