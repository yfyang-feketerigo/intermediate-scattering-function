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
	vector<double> q;
public:
	isf();
	isf(double _time, const vector<double>& _q);
	void compute(const vector<particle>& pv);

	inline double get_time() { return time; };
	inline double get_re() { return real; };
	inline double get_im() { return imagine; };
	inline double get_mod() { return module; };
	inline vector<double> get_isf() { return { time, real, imagine, module }; };
};

template <typename T>
double dot(const vector<T>& a, const vector<T>& b);

template<typename T>
inline double dot(const vector<T>& a, const vector<T>& b)
{
	if (a.size() != b.size())
	{
		cout << "vector size not equal while dot" << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		double sum = 0;
		for (size_t i = 0; i < a.size(); i++)
		{
			sum += a[i] * b[i];
		}
		return sum;
	}
}
