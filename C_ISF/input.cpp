#include "input.h"

input::input(string _fname, size_t _headline)
{
	fname = _fname;
	headline = _headline;
	linepointer = 0;
	infile.open(fname);
	totalline = 0;
	if (infile.is_open())
	{
		while (!infile.eof())
		{
			totalline += 1;
			infile.ignore(INT_MAX, '\n');
		}
		infile.close();
	}
	else
	{
		totalline = 0;
		cout << "open input file failed!" << endl;
		exit(EXIT_FAILURE);
	}
}


void input::open_file()
{
	if (!infile.is_open())
	{
		infile.open(fname);
	}
	else
	{
		cout << "input file has already been opened!" << endl;
		exit(EXIT_FAILURE);
	}
}

void input::close_file()
{
	if (infile.is_open())
	{
		infile.close();
	}
	else
	{
		cout << "input file is not opened!" << endl;
		exit(EXIT_FAILURE);
	}
}

void input::skiphead()
{
	if (infile.is_open())
	{
		if (linepointer == 0)
		{
			for (size_t i = 0; i < headline; i++)
			{
				infile.ignore(INT_MAX, '\n');
				linepointer += 1;
			}
		}
		else
		{
			cout << "head lines in file has already been skipped!" << endl;
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		throw "input file not opened!";
	}
}

size_t input::move_to_line(size_t _line)
{
	if (_line > totalline)
	{
		cout << "out of file line range!" << endl;
		return linepointer;
	}
	infile.close();
	infile.open(fname);
	for (size_t i = 1; i < _line; i++)
	{
		infile.ignore(INT_MAX, '\n');
	}
	return linepointer = _line;
}

size_t input::read_line()
{
	string line;
	if (infile.is_open())
	{
		if (infile.eof())
		{
			cout << "reach eof!" << endl;
			cout << "data remain unchanged!" << endl;
			return 0;
		}
		else
		{
			//cout << "reading " << linepointer << "th line." << endl;
			data.clear();
			getline(infile, line);
			trim(line);
			istringstream ss(line);
			while (!ss.eof())
			{
				double tmp;
				ss >> tmp;
				data.push_back(tmp);
			}
			linepointer += 1;
			return data.size();
		}
	}
	else
	{
		cout << "input file is not open!" << endl;
		exit(EXIT_FAILURE);
	}


}


bool input::check_EOF() const
{
	if (infile.eof())
	{
		return true;
	}
	else
	{
		return false;
	}
}

string& trim(string& s)
{
	if (s.empty()) return s;
	s.erase(0, s.find_first_not_of(' '));
	s.erase(s.find_last_not_of(' ') + 1);
	return s;
}
