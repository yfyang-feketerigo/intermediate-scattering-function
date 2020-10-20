#include<iostream>
#include<string>
#include"isf.h"
#include"particle.h"
#include"input.h"
#include"output.h"
#include "num_to_string.h"
using namespace std;

int main()
{
	const size_t IFILE_HEADLINES = 9;
	const size_t PARTICLE_DATASIZE = 6;
	const double TIMESTEP = 0.0025;

	double q_module;

	size_t init_step, end_step;
	string ifilename_prefix;
	cout << "enter initial timestep, end timestep, q, filename prefix:" << endl;
	cin >> init_step >> end_step >> q_module >> ifilename_prefix;
	//ifile.read_line();

	size_t id;
	ptype::ptype ptp;
	array<double, 4> dr;
	double time;
	vector<particle> pv;

	double q_tmp = 1. / sqrt(3.) * q_module;
	array <double, 3> q = { q_tmp,q_tmp,q_tmp };
	isf isf_obj(0., q);

	string ifilename;
	input ifile;
	ifile.set_headline(IFILE_HEADLINES);

	string ofilename = "isf." + ifilename_prefix;
	output ofile(ofilename);
	ofile.open_file();
	ofile.set_format(oformat::scientfic);

	size_t delta_step = 1;
	for (size_t step = init_step; step < end_step + 1; step += delta_step)
	{
		ifilename = ifilename_prefix + '.' + number_to_string(step);
		//cout << ifilename << endl;
		ifile.set_filename(ifilename);
		if (ifile.open_file())
		{
			time = (double)step * TIMESTEP;
			ifile.skiphead();
			size_t lcounter = IFILE_HEADLINES;
			while (!ifile.check_EOF() && ifile.read_line() != 0)
			{
				lcounter++;
				//cout << ifile.get_data().size() << endl;
				if (ifile.get_data().size() != PARTICLE_DATASIZE)
				{
					cout << "file: " << ifile.get_fname() << ": wrong data size " << ifile.get_data().size() << " at line " << lcounter << endl;
					cout << "data: " << ifile.get_data()[0] << endl;
				}
				else
				{
					id = (size_t)ifile.get_data()[0];
					ptp = (ptype::ptype)(int)ifile.get_data()[1];
					for (size_t i = 0; i < 4; i++)
					{
						dr.at(i) = ifile.get_data()[i + 2];
					}
					pv.push_back(particle(time, id, ptp, dr));
				}
			}
			ifile.close_file();
			cout << pv.size() << endl;
			isf_obj.set_time(time);
			isf_obj.compute(pv);
			//cout << isf_test.get_time() << ' ' << isf_test.get_im() << ' ' << isf_test.get_re() << endl;
			//vector<double> isf_vector({ isf_test.get_time(),isf_test.get_im(),isf_test.get_re(),isf_test.get_mod() });
			ofile.write_line(isf_obj.get_isf());
			pv.clear();
		}
		if (step == 10000)
		{
			delta_step = 100;
		}
		if (step == 1000000)
		{
			delta_step = 1000;
		}
	}


}