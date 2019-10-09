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
	vector<double> dr;
	double d, time;

	vector<particle> pv;

	input ifile(ifilename);

	ifile.open_file();



}