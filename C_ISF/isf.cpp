#include "isf.h"

isf::isf()
{
	time = real = imagine = module = 0.;
	q = { 0.,0.,0. };
}

isf::isf(double _time, const vector<double>& _q)
{
	time = _time;
	q = _q;
	real = real = imagine = module = 0.;
}

void isf::compute(const vector<particle>& pv)
{
	double sum_im = 0.;
	double sum_re = 0.;
	if (pv.empty())
	{
		cout << "partcile vector is empty!" << endl;
		exit(EXIT_FAILURE);
	}
	if (time != pv.front().get_time)
	{
		cout << "time not matched!" << endl;
		exit(EXIT_FAILURE);
	}
	for (size_t i = 0; i < pv.size() - 1; i++)
	{
		if (pv[i].get_time() != pv[i + 1].get_time())
		{
			cout << "unmatched particle time found: " << (i + 1) << endl;
			exit(EXIT_FAILURE);
		}
		else
		{
			sum_im += sin(dot(q, pv[i].get_dr()));
			sum_re += cos(dot(q, pv[i].get_dr()));
		}
	}
	sum_im += sin(dot(q, pv.back().get_dr()));
	sum_re += cos(dot(q, pv.back().get_dr()));
	imagine = sum_im / pv.size();
	real = sum_re / pv.size();
	module = sqrt(imagine * imagine + real * real);
}



