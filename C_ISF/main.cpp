//20210316 v2改进读取DPM文件的方法。
//20210316 添加扫描指定文件夹，获得特定文件名的容器，并且按文件后缀排序的函数
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
	//以下均为变量初始化、读入参数、设定格式
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
	//以上均为变量初始化、读入参数、设定格式
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
	//开始对时间循环

	cout << "starting time loop..." << endl;
	for (size_t i = 0; i < fpath_container.size(); i++)
	{
		ifilename = fpath_container[i].string();
		ifile.set_filename(ifilename);//读入文件
		if (ifile.open_file())//如果打开成功则计算，没有打开成功则跳过这一文件
		{
			string ext = fpath_container[i].extension().string();
			ext.erase(ext.begin());
			double time = stod(ext) * TIMESTEP;
			ifile.skiphead();//跳过文件头
			size_t lcounter = IFILE_HEADLINES;//读入行数统计
			while (!ifile.check_EOF() && ifile.read_line() != 0)//一行行读取文件直至文件末尾
			{
				lcounter++;
				if (ifile.get_data().size() != PARTICLE_DATASIZE)//检查文件每行的数据量是否符合预期
				{
					cout << "file: " << ifile.get_fname() << ": wrong data size " << ifile.get_data().size() << " at line " << lcounter << endl;
					cout << "data: " << ifile.get_data()[0] << endl;
				}
				else//确认无误，将文件每行的数据转化为粒子类对象，存入容器pv
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
			ifile.close_file();//读取完成
			cout << "from " << ifilename << " get " << pv.size() << " particle(s)" << endl;//输出容器pv大小，用于检查是否遗漏/增多粒子
			isf_obj.set_time(time);//设定时间
			cout << "time: " << time << endl;
			cout << "computing ISF..." << endl;
			isf_obj.compute(pv);//计算ISF
			ofile.write_line(isf_obj.get_isf());//输出ISF
			pv.clear();//清空粒子容器
			cout << "done." << endl;
		}
	}

	return 0;
}
/*
size_t delta_step = 1;
for (size_t step = init_step; step < end_step + 1; step += delta_step)
{
	ifilename = ifilename_prefix + '.' + number_to_string(step);//获得当前时刻储存粒子位移信息的文件名
	ifile.set_filename(ifilename);//读入文件
	if (ifile.open_file())//如果打开成功则计算，没有打开成功则跳过这一文件
	{
		time = (double)step * TIMESTEP;//将时间步换算成为LJ单位时间
		ifile.skiphead();//跳过文件头
		size_t lcounter = IFILE_HEADLINES;//读入行数统计
		while (!ifile.check_EOF() && ifile.read_line() != 0)//一行行读取文件直至文件末尾
		{
			lcounter++;
			if (ifile.get_data().size() != PARTICLE_DATASIZE)//检查文件每行的数据量是否符合预期
			{
				cout << "file: " << ifile.get_fname() << ": wrong data size " << ifile.get_data().size() << " at line " << lcounter << endl;
				cout << "data: " << ifile.get_data()[0] << endl;
			}
			else//确认无误，将文件每行的数据转化为粒子类对象，存入容器pv
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
		ifile.close_file();//读取完成
		cout << pv.size() << endl;//输出容器pv大小，用于检查是否遗漏/增多粒子
		isf_obj.set_time(time);//设定时间
		isf_obj.compute(pv);//计算ISF
		ofile.write_line(isf_obj.get_isf());//输出ISF
		pv.clear();//清空粒子容器
	}
	*/
	//增大时间间隔以提高效率
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



