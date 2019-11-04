//used to transfer number data type to string data type
//yfyang@ciac.ac.cn
#pragma once
#include <string>
#include <sstream>
using std::string;
using std::ostringstream;

template <typename T>
string number_to_string(T num, size_t precision); //transfer number data type to string data type, with SPECIFIED precision

template <typename T>
string number_to_string(T num);  //transfer number data type to string data type, with DEFAULT precision

template<typename T>
string number_to_string(T num, size_t precision)
{
	ostringstream oss;
	oss.precision(precision);
	oss << num;
	return oss.str();
}

template<typename T>
inline string number_to_string(T num)
{
	ostringstream oss;
	oss << num;
	return oss.str();
}
