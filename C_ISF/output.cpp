#include "output.h"



output::output(string _fname)
{
	fname = _fname;
}

output::output(string _fname, int _effectnum)
{
	fname = _fname;
	effectnum = _effectnum;
	headlines.clear();
}

output::output(string _fname, int _effectnum, vector<string> headlines)
{
	fname = _fname;
	effectnum = _effectnum;
	headlines = headlines;
}

bool output::open_file()
{
	outfile.open(fname);
	if (outfile.is_open())
	{
		return true;
	}
	return false;
}

bool output::close_file()
{
	outfile.close();
	if (!outfile.is_open())
	{
		return true;
	}
	return false;
}

void output::set_format(oformat _of)
{

	of = _of;
	if (_of == oformat::fixed)
	{
		outfile.setf(ios::fixed | ios::showpoint | ios::right);
	}
	else if (_of == oformat::scientfic)
	{
		outfile.setf(ios::scientific | ios::showpoint | ios::right);
	}
	else
	{
		cout << "unknown format!" << endl;
	}
}

void output::set_format(oformat _of, int _effectnum)
{
	effectnum = _effectnum;
	of = _of;
	if (_of == oformat::fixed)
	{
		outfile.setf(ios::fixed | ios::showpoint | ios::right);
	}
	else if (_of == oformat::scientfic)
	{
		outfile.setf(ios::scientific | ios::showpoint | ios::right);
	}
	else
	{
		cout << "unknown format!" << endl;
	}
}

size_t output::write_head()
{
	write_line(headlines);
	return headlines.size();
}


