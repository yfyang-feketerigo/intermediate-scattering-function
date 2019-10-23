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
	ifstream infile;
	string fname;
	size_t headline;
	size_t linepointer;
	vector<double> data;
	size_t totalline;
public:
	input(string _fname, size_t _headline);
	input();

	inline string get_fname() { return fname; };
	inline vector<double> get_data() const { return data; }
	inline size_t get_linep() const { return linepointer; }
	inline size_t get_totall() const { return totalline; }

	inline void reset_filename(string _fname) { fname = _fname; };
	bool open_file();
	void close_file();
	void skiphead();
	size_t move_to_line(size_t _line);
	size_t read_line();


	bool check_EOF() const;
};

