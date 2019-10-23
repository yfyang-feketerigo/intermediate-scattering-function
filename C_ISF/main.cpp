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
	string ifilename = "dpm.0.44.0";
	string ofilename = "test.isf.txt";
	input ifile(ifilename, IFILE_HEADLINES);

	//ifile.read_line();

	size_t id;
	ptype::ptype ptp;
	array<double, 4> dr;
	double time = 100000000 * 0.0025;
	vector<particle> pv;

	double qsingle = 1. / sqrt(3.) * 7.36;
	array <double, 3> q = { qsingle,qsingle,qsingle };
	isf isf_test(0., q);
	output ofile(ofilename);
	ofile.open_file();
	ofile.set_format(oformat::scientfic);

	for (size_t step = 0; step < 100; step++)
	{
		ifilename = "dpm.0.44." + number_to_string(step);
		//cout << ifilename << endl;
		ifile.reset_filename(ifilename);
		if (ifile.open_file())
		{
			time = (double)step * 0.0025;
			ifile.skiphead();
			size_t lcounter = IFILE_HEADLINES;
			while (!ifile.check_EOF())
			{
				ifile.read_line();
				lcounter++;
				//cout << ifile.get_data().size() << endl;
				if (ifile.get_data().size() != PARTICLE_DATASIZE)
				{
					cout << "file: " << ifile.get_fname() << ": wrong data size " << ifile.get_data().size() << " at line " << lcounter << endl;
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
			isf_test.set_time(time);
			isf_test.compute(pv);
			//cout << isf_test.get_time() << ' ' << isf_test.get_im() << ' ' << isf_test.get_re() << endl;
			//vector<double> isf_vector({ isf_test.get_time(),isf_test.get_im(),isf_test.get_re(),isf_test.get_mod() });
			ofile.write_line(isf_test.get_isf());
			pv.clear();
		}
	}

	/*cout << pv.size() << endl;
	for (size_t i = 0; i < pv.size(); i++)
	{
		cout << pv[i].get_id() << ' ' << pv[i].get_ptype() << ' ';
		for (size_t i1 = 0; i1 < 3; i1++)
		{
			cout << pv[i].get_displacement()[i1] << ' ';
		}
		cout << endl;
	}
	return 0;*/

}