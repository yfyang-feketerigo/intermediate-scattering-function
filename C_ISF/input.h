//this class is used to read data dumped(with 'dump'/'fix' command by lammps
//yfyang@ciac.ac.cn
#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
string& trim(string& s);
class input
{
private:
	ifstream infile; //input unit, ifstream class
	string fname; //input data file name
	size_t headline; //description line number
	size_t linepointer; //point to line that have read
	vector<double> data; //store numerical data in a line
	size_t totalline; //total line of this input file
public:
	input(string _fname, size_t _headline); //constructor with input file name & number of description lines
	input(); //default constructor

	inline string get_fname() { return fname; } //return file name
	inline vector<double> get_data() const { return data; } //return data with a vector
	inline size_t get_linep() const { return linepointer; } //return line pointer
	inline size_t get_totall() const { return totalline; } //return total lines of file

	inline void set_headline(size_t _headline) { headline = _headline; }; //set number of description lines
	inline void set_filename(string _fname) { fname = _fname; }; // set file name
	bool open_file(); //open input file
	void close_file(); //close input file
	void skiphead(); //skip description lines in the head of input file
	size_t move_to_line(size_t _line); //move to line
	size_t read_line(); //read a line of data then ready to read next line



	bool check_EOF() const; //check eof
};

