#pragma once
#include <vector>
class OutputClass
{
public:
	OutputClass();
	~OutputClass();

	static void Output(const std::string & outputFile, const std::vector<double> & allocTime, const std::vector<double> & readTime, const std::vector<double> & randomAccessTimes);
};

