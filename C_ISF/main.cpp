#include<iostream>
#include<string>
#include"isf.h"
#include"particle.h"
#include"input.h"
#include"output.h"

using namespace std;

int main()
{
	string ifilename;
	string ofilename;
	vector<double> q = { 0,7.4,0 };

	input ifile;

	//ifile.read_line();

	size_t id;
	ptype ptp;
	array<double, 4> dr;
	double time;
	vector<particle> pv;

	ifile.open_file();
	ifile.skiphead();
	while (!ifile.check_EOF())
	{
		ifile.read_line();
		id = (size_t)ifile.get_data()[0];
		ptp = (ptype)(int)ifile.get_data()[1];
		for (size_t i = 0; i < 4; i++)
		{
			dr.at(i) = ifile.get_data()[i + 2];
		}
		pv.push_back(particle(time, id, ptp, dr));
	}
	ifile.close_file();
}