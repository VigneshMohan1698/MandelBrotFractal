#pragma once
#include <complex>
class MandelBrot
{
public:
	MandelBrot();
	static const int MAX_ITERATIONS = 1000;
	static int getIterations(double x, double y);
};

