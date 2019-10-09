#pragma once
#include <string>
#include <sstream>
using std::string;
using std::ostringstream;

template <typename T>
string number_to_string(T num, size_t precision);

template <> string number_to_string(int num);

template<typename T>
string number_to_string(T num, size_t precision)
{
	ostringstream oss;
	oss.precision(precision);
	oss << num;
	return oss.str();
}

template <> string number_to_string(int num)
{
	ostringstream oss;
	oss << num;
	return oss.str();
}


