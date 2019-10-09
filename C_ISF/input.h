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
	input(string _fname, size_t _headline = 0);

	inline vector<double> get_data() const { return data; }
	inline size_t get_linep() const { return linepointer; }
	inline size_t get_totall() const { return totalline; }

	void open_file();
	void close_file();
	void skiphead();
	size_t move_to_line(size_t _line);
	size_t read_line();


	bool check_EOF() const;
};

