#include "point.h"
#include <map>
#include <vector>
#include "time.h"

#ifndef TYPES_H
#define TYPES_H

using namespace std;

typedef map<Point2D, int> PointCloud;
typedef vector<Point2D> Points;
enum Status {FEASIBLE, INFEASIBLE};
typedef pair<int, double> Coeff;
typedef vector<Coeff> Coeffs;
typedef clock_t Time;

#endif
