#include "OutputClass.h"
#include <fstream>
#include <limits>
#include <iostream>

typedef std::numeric_limits< double > dbl;



OutputClass::OutputClass()
{
}


OutputClass::~OutputClass()
{
}

bool file_exists(const std::string& filename)
{
	struct stat buf;
	return stat(filename.c_str(), &buf) != -1;
}

void OutputClass::Output(const std::string& outputFile, const std::vector<double>& allocTime,
	const std::vector<double> & readTime, const std::vector<double> & randomAccessTimes)
{
	using namespace std;

	const bool exist = file_exists(outputFile);
	std::cout << "Start Output: " << outputFile.c_str() << std::endl;
	ofstream out(outputFile, ofstream::out | ofstream::app);
	

	out.precision(dbl::max_digits10);

	if (!exist)
	{
		out << "Alloc\t" << "ReadTime\t" << "Random" << std::endl;
	}

	for (size_t i = 0; i < allocTime.size(); i++)
	{
		out << allocTime[i] << "\t" << readTime[i] << "\t" << randomAccessTimes[i] << std::endl;
	}

	out.close();
	std::cout << "End Output: " << outputFile.c_str() << std::endl;

}
