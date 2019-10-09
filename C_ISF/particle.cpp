#include "particle.h"

particle::particle()
{
	type = ptype::none;
	time = 0.;
	dx = dy = dz = d = 0.;
	group = gtype::none;
}

particle::particle(double _time, ptype _type, const vector<double>& dpm)
{
	if (dpm.size() == 4)
	{
		dx = dpm[0];
		dy = dpm[1];
		dz = dpm[2];
		d = dpm[3];
	}
	else
	{
		cout << "wrong particle initialize parameter!" << endl;
		dx = dy = dz = d = 0.;
	}
	group = gtype::none;
	type = _type;
	time = _time;
}

void particle::set_displacement(const vector<double>& dpm)
{
	if (dpm.size() == 4)
	{
		dx = dpm[0];
		dy = dpm[1];
		dz = dpm[2];
		d = dpm[3];
	}
	else
	{
		cout << "wrong particle initialize parameter!" << endl;
		dx = dy = dz = 0.;
	}
}

void sort_d(vector<particle>& _pv)
{
	for (size_t i = 0; i < (_pv.size() - 1); i++)
	{
		for (size_t j = 0; j < (_pv.size() - i - 1); j++)
		{
			if (_pv[i].get_d() > _pv[j].get_d())
			{
				swap(_pv[i], _pv[j]);
			}
		}
	}
}

size_t set_gtype(vector<particle>& _pvsort, double _thershold)
{
	size_t i = 0;
	for (i = 0; i < (_pvsort.size() * _thershold); i++)
	{
		_pvsort[i].set_group(gtype::sd);
	}
	for (; i < (_pvsort.size() - _pvsort.size() * _thershold); i++)
	{
		_pvsort[i].set_group(gtype::md);
	}
	for (; i < _pvsort.size() - 1; i++)
	{
		_pvsort[i].set_group(gtype::ld);
	}
	return i;
}

const vector<particle> get_group(const vector<particle>& _pv, gtype _group)
{
	vector<particle> pv_group;
	for (size_t i = 0; i < _pv.size(); i++)
	{
		if (_pv[i].get_gtype() == _group)
		{

		}
	}
	return vector<particle>();
}