#pragma once
#include <vector>
#include "ResultsLib.h"
class Tester
{
public:
	const char* file;
	Tester() : file("heroesv2.results")
	{
		std::vector<const char*> codeFiles{ "HeroesDB.h", "HeroesDB.cpp", "HeroesV2.cpp" };
		results::WriteResults(codeFiles, file);
	}

	void ShowResults()
	{
		results::ReadResults(file, std::chrono::seconds(900));
	}
};

