#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
const int DEFAULT_EFFECT_NUM = 6;
const int INTERVAL = 8;

enum oformat
{
	scientfic,
	fixed
};


class output
{
private:
	string fname;
	vector<string> headlines;
	ofstream outfile;
	int effectnum = DEFAULT_EFFECT_NUM;
	size_t linecounter = 0;
	oformat of = oformat::scientfic;
public:
	output(string _fname);
	output(string _fname, int _effectnum);
	output(string _fname, int _effectnum, vector<string> headlines);
	bool open_file();
	bool close_file();
	inline void set_effectNum(int _en) { effectnum = _en; };
	inline void set_headlines(vector<string> _headlines) { headlines = _headlines; };

	void set_format(oformat _of);
	void set_format(oformat _of, int _effectnum);


	template<typename T>
	size_t write_line(vector<T> vec);
	template<> size_t write_line(vector<string> vec);

	size_t write_head();
};

template<typename T>
size_t output::write_line(vector<T> vec)
{
	if (!outfile.is_open())
	{
		cout << "output file not open!" << endl;
		return 0;
	}
	if (oformat::scientfic == of)
	{
		for (size_t i = 0; i < vec.size(); i++)
		{
			outfile.width((long long)effectnum + INTERVAL);
			outfile << setprecision((long long)effectnum - 1) << vec[i] << ' ';
		}
		outfile << endl;
		linecounter += 1;
	}
	else if (oformat::fixed == of)
	{
		for (size_t i = 0; i < vec.size(); i++)
		{
			outfile.width((long long)effectnum + INTERVAL);
			outfile << setprecision(effectnum) << vec[i] << ' ';
		}
		outfile << endl;
		linecounter += 1;
	}
	return linecounter;
}

template<> size_t output::write_line(vector<string> vec)
{
	if (!outfile.is_open())
	{
		cout << "output file not open!" << endl;
	}
	for (size_t i = 0; i < vec.size(); i++)
	{
		outfile << vec[i] << endl;
	}
	linecounter += 1;
	return linecounter;
}