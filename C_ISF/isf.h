#pragma once
#include <iostream>
#include "particle.h"
#include <vector>
using namespace ::std;

class isf
{
private:
	double time;
	double real;
	double imagine;
	double module;
	array<double, 3> q;
public:
	isf();
	isf(double _time, const array <double, 3> & _q);
	void compute(const vector<particle>& pv);

	inline double get_time() { return time; };
	inline double get_re() { return real; };
	inline double get_im() { return imagine; };
	inline double get_mod() { return module; };
	inline vector<double> get_isf() { return { time, real, imagine, module }; };
};

template <typename T>
double dot(const array<T, 3> & a, const array<T, 3> & b);

template<typename T>
inline double dot(const array<T, 3> & a, const array<T, 3> & b)
{
	double sum = 0;
	for (size_t i = 0; i < a.size(); i++)
	{
		sum += a[i] * b[i];
	}
	return sum;
}
