//ISF类，用于计算ISF
#pragma once
#include <iostream>
#include "particle.h"
#include <vector>
using namespace ::std;

class isf
{
private:
	double time; //当前时间
	double real; //ISF实部，采用cos(q·r)/(|q|*|r|)的算法，其中q大小是结构因子第一主峰，方向任意（此处选取qx=qy=qz)
	double imagine; //ISF虚部，采用sin(q·r)/(|q|*|r|)的算法，其中q大小是结构因子第一主峰，方向任意（此处选取qx=qy=qz)
	double module; // sqrt(real*real+imagine*imagine)
	double real_iso;//已知体系为各项均匀时，ISF=sin(|q|*|r|)/(|q|*|r|)，在KA模型中，real_iso≈real（相差百分之1以内）
	array<double, 3> q;//其中q大小是结构因子第一主峰，方向任意（此处选取qx=qy=qz)
public:
	isf();//默认构造函数
	isf(double _time, const array <double, 3>& _q);//构造函数
	void compute(const vector<particle>& pv);//传入粒子容器pv内所有粒子，并计算ISF的各项值

	inline void set_time(double _time) { time = _time; };//更改ISF时间

	inline double get_time() { return time; };//返回ISF的时间
	inline double get_re() { return real; };//返回real
	inline double get_im() { return imagine; };//返回imagine
	inline double get_mod() { return module; };//返回module
	inline double get_re_iso() { return real_iso; }//返回real_iso
	inline vector<double> get_isf() { return { time, real, real_iso,imagine, module }; };//以数组形式返回所有值
};

template <typename T>
double dot(const array<T, 3>& a, const array<T, 3>& b);//定义向量点乘

template<typename T>
inline double dot(const array<T, 3>& a, const array<T, 3>& b)
{
	double sum = 0;
	for (size_t i = 0; i < a.size(); i++)
	{
		sum += a[i] * b[i];
	}
	return sum;
}
