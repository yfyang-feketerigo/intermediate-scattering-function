//this class is used to write data in to a file;
//yfyang@ciac.ac.cn
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;


enum oformat //output format
{
	scientfic,
	fixed
};


class output
{
private:
	const int DEFAULT_EFFECT_NUM = 6;
	const int INTERVAL = 8; //interval space number between rows
	string fname;	//output data file name
	vector<string> headlines; //output data file description lines
	ofstream outfile; //output class, ofstream
	int effectnum = DEFAULT_EFFECT_NUM; // effect number of data
	size_t linecounter = 0; //number of total line been written to file
	oformat of = oformat::scientfic; //data format
public:
	output(string _fname);  //constructor
	output(string _fname, int _effectnum); //constructor with effect number
	output(string _fname, int _effectnum, vector<string> headlines); //constructor with effect number & description
	bool open_file(); //create & open file
	bool close_file(); //close file
	inline void set_effectNum(int _en) { effectnum = _en; }; //set effect number
	inline void set_headlines(vector<string> _headlines) { headlines = _headlines; }; //set description

	void set_format(oformat _of); //set data format
	void set_format(oformat _of, int _effectnum); //set data format with effect number


	template<typename T>
	size_t write_line(vector<T> vec);  //write a line to file with data(numerical data) in vector
	template<> size_t write_line(vector<string> vec); //write a line to file with desription(string data), the format is different from former one

	size_t write_head(); //write headline description defined before
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