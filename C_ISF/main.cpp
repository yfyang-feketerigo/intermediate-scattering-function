//20210316 v2�Ľ���ȡDPM�ļ��ķ�����
//20210316 ���ɨ��ָ���ļ��У�����ض��ļ��������������Ұ��ļ���׺����ĺ���
#include<iostream>
#include<string>
#include"isf.h"
#include"particle.h"
#include"input.h"
#include"output.h"
#include "num_to_string.h"
#include "get_files.h"
using namespace std;

int main()
{
	//���¾�Ϊ������ʼ��������������趨��ʽ
	const size_t IFILE_HEADLINES = 9;
	const size_t PARTICLE_DATASIZE = 6;
	const double TIMESTEP = 0.0025;

	double q_module;

	//size_t init_step, end_step;
	string ifilename_prefix;
	string dpm_dir;
	cout << "enter dpm_dir, q, filename prefix:" << endl;
	cin >> dpm_dir >> q_module >> ifilename_prefix;

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
	//���Ͼ�Ϊ������ʼ��������������趨��ʽ
	boost::filesystem::path dir_fullpath(dpm_dir);
	vector<boost::filesystem::path> fpath_container;
	fpath_container = GET_FILES::ScanFiles_stem(dpm_dir, ifilename_prefix);
	GET_FILES::Extension_sort(fpath_container);
	for (size_t i = 0; i < fpath_container.size(); i++)
	{
		cout << fpath_container[i].string() << endl;
	}
	cout << "dpm dir full path: " << dir_fullpath.string() << endl;
	cout << "q_module = " << q_module << endl;
	//��ʼ��ʱ��ѭ��

	cout << "starting time loop..." << endl;
	for (size_t i = 0; i < fpath_container.size(); i++)
	{
		ifilename = fpath_container[i].string();
		ifile.set_filename(ifilename);//�����ļ�
		if (ifile.open_file())//����򿪳ɹ�����㣬û�д򿪳ɹ���������һ�ļ�
		{
			string ext = fpath_container[i].extension().string();
			ext.erase(ext.begin());
			double time = stod(ext) * TIMESTEP;
			ifile.skiphead();//�����ļ�ͷ
			size_t lcounter = IFILE_HEADLINES;//��������ͳ��
			while (!ifile.check_EOF() && ifile.read_line() != 0)//һ���ж�ȡ�ļ�ֱ���ļ�ĩβ
			{
				lcounter++;
				if (ifile.get_data().size() != PARTICLE_DATASIZE)//����ļ�ÿ�е��������Ƿ����Ԥ��
				{
					cout << "file: " << ifile.get_fname() << ": wrong data size " << ifile.get_data().size() << " at line " << lcounter << endl;
					cout << "data: " << ifile.get_data()[0] << endl;
				}
				else//ȷ�����󣬽��ļ�ÿ�е�����ת��Ϊ��������󣬴�������pv
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
			ifile.close_file();//��ȡ���
			cout << "from " << ifilename << " get " << pv.size() << " particle(s)" << endl;//�������pv��С�����ڼ���Ƿ���©/��������
			isf_obj.set_time(time);//�趨ʱ��
			cout << "time: " << time << endl;
			cout << "computing ISF..." << endl;
			isf_obj.compute(pv);//����ISF
			ofile.write_line(isf_obj.get_isf());//���ISF
			pv.clear();//�����������
			cout << "done." << endl;
		}
	}

	return 0;
}
/*
size_t delta_step = 1;
for (size_t step = init_step; step < end_step + 1; step += delta_step)
{
	ifilename = ifilename_prefix + '.' + number_to_string(step);//��õ�ǰʱ�̴�������λ����Ϣ���ļ���
	ifile.set_filename(ifilename);//�����ļ�
	if (ifile.open_file())//����򿪳ɹ�����㣬û�д򿪳ɹ���������һ�ļ�
	{
		time = (double)step * TIMESTEP;//��ʱ�䲽�����ΪLJ��λʱ��
		ifile.skiphead();//�����ļ�ͷ
		size_t lcounter = IFILE_HEADLINES;//��������ͳ��
		while (!ifile.check_EOF() && ifile.read_line() != 0)//һ���ж�ȡ�ļ�ֱ���ļ�ĩβ
		{
			lcounter++;
			if (ifile.get_data().size() != PARTICLE_DATASIZE)//����ļ�ÿ�е��������Ƿ����Ԥ��
			{
				cout << "file: " << ifile.get_fname() << ": wrong data size " << ifile.get_data().size() << " at line " << lcounter << endl;
				cout << "data: " << ifile.get_data()[0] << endl;
			}
			else//ȷ�����󣬽��ļ�ÿ�е�����ת��Ϊ��������󣬴�������pv
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
		ifile.close_file();//��ȡ���
		cout << pv.size() << endl;//�������pv��С�����ڼ���Ƿ���©/��������
		isf_obj.set_time(time);//�趨ʱ��
		isf_obj.compute(pv);//����ISF
		ofile.write_line(isf_obj.get_isf());//���ISF
		pv.clear();//�����������
	}
	*/
	//����ʱ���������Ч��
	/*
	if (step == 10000)
	{
		delta_step = 100;
	}
	if (step == 1000000)
	{
		delta_step = 1000;
	}
	*/



