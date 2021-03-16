//20210316 添加扫描指定文件夹，获得特定文件名的容器，并且按文件后缀排序的函数
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/filesystem.hpp>


using std::string;
using std::vector;
using std::cerr;
using std::cout;
using std::endl;

namespace GET_FILES
{
	vector<boost::filesystem::path> ScanFiles_stem(const string directory_path, const string stem)
	{
		vector<boost::filesystem::path> filepath_container;

		boost::filesystem::path dfullpath(directory_path);
		if (!boost::filesystem::exists(dfullpath) || !boost::filesystem::is_directory(dfullpath))
		{
			cerr << "Directory: " << dfullpath.string() << " not exist!" << endl;
			throw ("Directory: " + dfullpath.string() + " not exist!");
		}

		boost::filesystem::recursive_directory_iterator end_iter;
		for (boost::filesystem::recursive_directory_iterator iter(dfullpath); iter != end_iter; iter++)
		{
			try
			{
				if (boost::filesystem::is_directory(*iter))
				{
					cout << *iter << " is dir" << endl;
				}
				else if (iter->path().stem().string() == stem
					&& boost::filesystem::is_regular_file(*iter))
				{
					filepath_container.push_back(iter->path());
				}
			}
			catch (const std::exception& err)
			{
				std::cerr << err.what() << endl;
				exit(1);
			}
		}
		return filepath_container;
	}

	bool Extension_GE(const boost::filesystem::path& fpath1, const boost::filesystem::path& fpath2)
	{
		const string& str_fex1 = fpath1.extension().string();
		const string& str_fex2 = fpath2.extension().string();
		int flen1 = str_fex1.length();
		int flen2 = str_fex2.length();
		if (flen1 < flen2)
		{
			return false;
		}
		else if (flen1 > flen2)
		{
			return true;
		}
		else
		{
			for (size_t i = 0; i < flen1; i++)
			{
				if (str_fex1[i] < str_fex2[i])
				{
					return false;
				}
				else if (str_fex1[i] > str_fex2[i])
				{
					return true;
				}
			}
		}
		return true;
	}

	bool Extension_LT(const boost::filesystem::path& fpath1, const boost::filesystem::path& fpath2)
	{
		return !Extension_GE(fpath1, fpath2);
	}

	void Extension_sort(vector<boost::filesystem::path>& fpath_container)
	{
		std::sort(fpath_container.begin(), fpath_container.end(), Extension_LT);
	}
}