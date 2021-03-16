//���ڼ���ISF
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
	double q_abs = sqrt(q[0] * q[0] + q[1] * q[1] + q[2] * q[2]);//����|q|
	if (pv.empty())//����ļ��Ƿ��
	{
		cout << "partcile vector is empty!" << endl;
		exit(EXIT_FAILURE);
	}
	if (time != pv.front().get_time())//�����������pv�ڵ������Ƿ��ǵ�ǰʱ�������
	{
		cout << "time not matched!" << endl;
		exit(EXIT_FAILURE);
	}
	for (size_t i = 0; i < pv.size() - 1; i++)//��������
	{
		if (pv[i].get_time() != pv[i + 1].get_time())//�����������pv�������ǲ�������ͬһʱ�������
		{
			cout << "unmatched particle time found: " << (i + 1) << endl;
			exit(EXIT_FAILURE);
		}
		else//����ISF�ĸ���ֵ
		{
			sum_im += sin(dot(q, pv[i].get_dr()));
			sum_re += cos(dot(q, pv[i].get_dr()));
			sum_re_iso += sin(q_abs * pv[i].get_d()) / q_abs / pv[i].get_d();
		}
	}
	sum_im += sin(dot(q, pv.back().get_dr()));//���������һ�����Ӽ���ISF
	sum_re += cos(dot(q, pv.back().get_dr()));
	sum_re_iso += sin(q_abs * pv.back().get_d()) / q_abs / pv.back().get_d();
	imagine = sum_im / pv.size();//ȡƽ��
	real = sum_re / pv.size();//ȡƽ��
	real_iso = sum_re_iso / pv.size();//ȡƽ��
	module = sqrt(imagine * imagine + real * real);//����module
}


