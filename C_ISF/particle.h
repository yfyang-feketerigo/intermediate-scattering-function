//class used to store particle information
//yfyang@ciac.ac.cn
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <array>
using namespace::std;

namespace gtype //define ls/sd/md group
{
	enum gtype
	{
		ld,
		sd,
		md,
		none
	};
};

namespace ptype //define particle type
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
	size_t id; //particle id
	ptype::ptype type = ptype::none; //particle type
	double time = 0; //time
	double dx = 0; //displacement in x direction
	double dy = 0; //displacement in y direction
	double dz = 0; //displacement in z direction
	double d = 0; //displacement, sqrt(x^2+y^2+z^2)
	gtype::gtype group = gtype::none; //gourp type

public:
	particle(); //default constructor, all data set to zero, all type set to default
	particle(double _time, size_t _id, ptype::ptype _type, const array<double, 4> & dpm); //constructor, displace information stored in array
	particle(double _time, size_t _id, ptype::ptype _type, const vector<double>& dpm);//constructor, vector version

	inline double get_time() const { return time; }; //return time
	inline array<double, 4> get_displacement() const { return { dx,dy,dz,d }; }; //return 4-size-array displacement information
	inline double get_d() const { return d; };//return displacement
	inline array<double, 3> get_dr() const { return{ dx,dy,dz }; };  //return 3-size-array diplacement, WITHOUT d
	inline gtype::gtype get_gtype() const { return group; }; //return group type
	inline ptype::ptype get_ptype() const { return type; }; //return particle type
	inline size_t get_id() const { return id; }; //return particle id

	inline void set_time(double _time) { time = _time; }; //set time
	void set_displacement(const array<double, 4> & dpm); //set displacement(4-size-array version)
	inline void set_group(gtype::gtype _group) { group = _group; }; //set particle group
};

void sort_d(vector<particle>& _pv);
size_t set_gtype(vector<particle>& _pvsort, double _thershold);
const vector<particle> seek_group(const vector<particle>& _pv, gtype::gtype _group);
const particle& seek_id(const vector<particle>& pv, size_t _id);