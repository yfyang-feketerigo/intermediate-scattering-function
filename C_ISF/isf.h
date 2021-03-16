//ISF�࣬���ڼ���ISF
#pragma once
#include <iostream>
#include "particle.h"
#include <vector>
using namespace ::std;

class isf
{
private:
	double time; //��ǰʱ��
	double real; //ISFʵ��������cos(q��r)/(|q|*|r|)���㷨������q��С�ǽṹ���ӵ�һ���壬�������⣨�˴�ѡȡqx=qy=qz)
	double imagine; //ISF�鲿������sin(q��r)/(|q|*|r|)���㷨������q��С�ǽṹ���ӵ�һ���壬�������⣨�˴�ѡȡqx=qy=qz)
	double module; // sqrt(real*real+imagine*imagine)
	double real_iso;//��֪��ϵΪ�������ʱ��ISF=sin(|q|*|r|)/(|q|*|r|)����KAģ���У�real_iso��real�����ٷ�֮1���ڣ�
	array<double, 3> q;//����q��С�ǽṹ���ӵ�һ���壬�������⣨�˴�ѡȡqx=qy=qz)
public:
	isf();//Ĭ�Ϲ��캯��
	isf(double _time, const array <double, 3>& _q);//���캯��
	void compute(const vector<particle>& pv);//������������pv���������ӣ�������ISF�ĸ���ֵ

	inline void set_time(double _time) { time = _time; };//����ISFʱ��

	inline double get_time() { return time; };//����ISF��ʱ��
	inline double get_re() { return real; };//����real
	inline double get_im() { return imagine; };//����imagine
	inline double get_mod() { return module; };//����module
	inline double get_re_iso() { return real_iso; }//����real_iso
	inline vector<double> get_isf() { return { time, real, real_iso,imagine, module }; };//��������ʽ��������ֵ
};

template <typename T>
double dot(const array<T, 3>& a, const array<T, 3>& b);//�����������

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
