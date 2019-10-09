#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace::std;

enum gtype
{
	ld,
	sd,
	md,
	none
};

enum ptype
{
	A,
	B,
	none
};

class particle
{
private:
	ptype type = ptype::none;
	double time = 0;
	double dx = 0;
	double dy = 0;
	double dz = 0;
	double d = 0;
	gtype group = gtype::none;

public:
	particle();
	particle(double _time, ptype _type, const vector<double>& dpm);


	inline double get_time() const { return time; };
	inline vector<double> get_displacement() const { return { dx,dy,dz,d }; };
	inline double get_d() const { return d; };
	inline vector <double> get_dr() const { return{ dx,dy,dz }; };
	inline gtype get_gtype() const { return group; };
	inline ptype get_ptype() const { return type; };

	inline void set_time(double _time) { time = _time; };
	void set_displacement(const vector<double>& dpm);
	inline void set_group(gtype _group) { group = _group; };
};

void sort_d(vector<particle>& _pv);
size_t set_gtype(vector<particle>& _pvsort, double _thershold);
const vector<particle> get_group(const vector<particle>& _pv, gtype _group);