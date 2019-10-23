#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <array>
using namespace::std;

namespace gtype
{
	enum gtype
	{
		ld,
		sd,
		md,
		none
	};
};

namespace ptype
{
	enum ptype
	{
		none,
		A,
		B
	};
};

class particle
{
private:
	size_t id;
	ptype::ptype type = ptype::none;
	double time = 0;
	double dx = 0;
	double dy = 0;
	double dz = 0;
	double d = 0;
	gtype::gtype group = gtype::none;

public:
	particle();
	particle(double _time, size_t _id, ptype::ptype _type, const array<double, 4> & dpm);
	particle(double _time, size_t _id, ptype::ptype _type, const vector<double>& dpm);

	inline double get_time() const { return time; };
	inline array<double, 4> get_displacement() const { return { dx,dy,dz,d }; };
	inline double get_d() const { return d; };
	inline array<double, 3> get_dr() const { return{ dx,dy,dz }; };
	inline gtype::gtype get_gtype() const { return group; };
	inline ptype::ptype get_ptype() const { return type; };
	inline size_t get_id() const { return id; };

	inline void set_time(double _time) { time = _time; };
	void set_displacement(const array<double, 4> & dpm);
	inline void set_group(gtype::gtype _group) { group = _group; };
};

void sort_d(vector<particle>& _pv);
size_t set_gtype(vector<particle>& _pvsort, double _thershold);
const vector<particle> seek_group(const vector<particle>& _pv, gtype::gtype _group);
const particle& seek_id(const vector<particle>& pv, size_t _id);