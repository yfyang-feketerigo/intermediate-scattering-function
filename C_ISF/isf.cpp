//用于计算ISF
#include "isf.h"

isf::isf()
{
	time = real = imagine = module = 0.;
	real_iso = 0.;
	q = { 0.,0.,0. };
}

isf::isf(double _time, const array <double, 3>& _q)
{
	time = _time;
	q = _q;
	real = imagine = module = 0.;
}

void isf::compute(const vector<particle>& pv)
{
	double sum_im = 0.;
	double sum_re = 0.;
	double sum_re_iso = 0.;
	double q_abs = sqrt(q[0] * q[0] + q[1] * q[1] + q[2] * q[2]);//计算|q|
	if (pv.empty())//检查文件是否打开
	{
		cout << "partcile vector is empty!" << endl;
		exit(EXIT_FAILURE);
	}
	if (time != pv.front().get_time())//检查粒子容器pv内的粒子是否是当前时间的粒子
	{
		cout << "time not matched!" << endl;
		exit(EXIT_FAILURE);
	}
	for (size_t i = 0; i < pv.size() - 1; i++)//遍历粒子
	{
		if (pv[i].get_time() != pv[i + 1].get_time())//检查粒子容器pv内粒子是不是属于同一时间的粒子
		{
			cout << "unmatched particle time found: " << (i + 1) << endl;
			exit(EXIT_FAILURE);
		}
		else//计算ISF的各项值
		{
			sum_im += sin(dot(q, pv[i].get_dr()));
			sum_re += cos(dot(q, pv[i].get_dr()));
			sum_re_iso += sin(q_abs * pv[i].get_d()) / q_abs / pv[i].get_d();
		}
	}
	sum_im += sin(dot(q, pv.back().get_dr()));//容器内最后一个粒子计算ISF
	sum_re += cos(dot(q, pv.back().get_dr()));
	sum_re_iso += sin(q_abs * pv.back().get_d()) / q_abs / pv.back().get_d();
	imagine = sum_im / pv.size();//取平均
	real = sum_re / pv.size();//取平均
	real_iso = sum_re_iso / pv.size();//取平均
	module = sqrt(imagine * imagine + real * real);//计算module
}


