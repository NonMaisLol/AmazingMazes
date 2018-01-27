/*
 * main.cpp
 *
 *  Created on: Jan 3, 2018
 *      Author: Pascal Assens
 */

#include	<iostream>
#include	<memory>
#include	<unordered_map>
#include	<stdlib.h>

#include 	"MazeTester.hpp"

std::string		error_msg = "";

bool	PrintString(const char* fname)
{
	std::unique_ptr<AMazeAnalyst>		m;

	try
	{
		m = std::make_unique<MazeAnalyst>(fname);
	}
	catch (const std::exception& e)
	{
		error_msg = e.what();
		return (false);
	}

	m->Explore();
	std::cout << m->ToString() << std::endl;
	return (true);
}

int		main(int ac, char** av)
{
	if (ac != 5)
	{
		std::cout << "Bad Parameters." << std::endl;
		return (1);
	}

	std::unordered_map<std::string, MazeTester::eTest> tests = {
		{ "Format", MazeTester::e_format },
		{ "Wayout", MazeTester::e_wayout },
		{ "Perfect", MazeTester::e_perfect },
		{ "RPerfect", MazeTester::e_rperfect },
		{ "RRPerfect", MazeTester::e_rrperfect },
		{ "Imperfect", MazeTester::e_imperfect }
	};
	MazeTester	mt;
	uint		w = 0;
	uint		h = 0;

	PrintString(av[1]);

	try
	{
		w = atoi(av[2]);
		h = atoi(av[3]);
		std::cout << (mt.RunTest(av[1], w, h, tests[av[4]]) == true ? "OK" : "KO") << std::endl;
		std::cout << mt.GetMessage() << std::endl;
	} catch (const std::exception& e)
	{
		std::cout << "FATAL ERROR !: " << e.what() << std::endl;
		return (1);
	}

	return (0);
}
