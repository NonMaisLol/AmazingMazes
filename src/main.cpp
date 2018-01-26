/*
 * main.cpp
 *
 *  Created on: Jan 3, 2018
 *      Author: Pascal Assens
 */

#include	<iostream>
#include	<memory>
#include	<unordered_map>

#include 	"MazeAnalyst.hpp"

std::string		error_msg = "";

bool	RunTest_FORMAT(const char* fname, uint w, uint h)
{
	std::unique_ptr<AMazeAnalyst>		m;

	try
	{
		m = std::make_unique<MazeAnalyst>(fname);
	}
	catch (const MazeError& e)
	{
		error_msg = e.what();
		return (false);
	}

	if (m->GetWidth() != w || m->GetHeight() != h)
	{
		error_msg = "Size is such wrong !";
		return (false);
	}
	return (true);
}

bool	RunTest_WAYOUT(const char* fname)
{
	std::unique_ptr<AMazeAnalyst>		m;

	try
	{
		m = std::make_unique<MazeAnalyst>(fname);
	}
	catch (const MazeError& e)
	{
		error_msg = e.what();
		return (false);
	}

	m->Explore();
	if (m->GetWayOut() == true)
	{
		return (true);
	}

	return (false);
}

bool	RunTest_ISPERFECT(const char* fname)
{
	std::unique_ptr<AMazeAnalyst>		m;

	try
	{
		m = std::make_unique<MazeAnalyst>(fname);
	}
	catch (const MazeError& e)
	{
		error_msg = e.what();
		return (false);
	}

	m->Explore();
	if (m->GetType() == AMazeAnalyst::e_perfect ||
		m->GetType() == AMazeAnalyst::e_rperfect ||
		m->GetType() == AMazeAnalyst::e_rrperfect)
	{
		return (true);
	}

	return (false);
}

bool	RunTest_ISRPERFECT(const char* fname)
{
	std::unique_ptr<AMazeAnalyst>		m;

	try
	{
		m = std::make_unique<MazeAnalyst>(fname);
	}
	catch (const MazeError& e)
	{
		error_msg = e.what();
		return (false);
	}

	m->Explore();
	if (m->GetType() == AMazeAnalyst::e_rperfect ||
		m->GetType() == AMazeAnalyst::e_rrperfect)
	{
		return (true);
	}

	return (false);
}

bool	RunTest_ISRRPERFECT(const char* fname)
{
	std::unique_ptr<AMazeAnalyst>		m;

	try
	{
		m = std::make_unique<MazeAnalyst>(fname);
	}
	catch (const MazeError& e)
	{
		error_msg = e.what();
		return (false);
	}

	m->Explore();
	if (m->GetType() == AMazeAnalyst::e_rrperfect)
	{
		return (true);
	}

	return (false);
}

bool	RunTest_ISIMPERFECT(const char* fname)
{
	std::unique_ptr<AMazeAnalyst>		m;

	try
	{
		m = std::make_unique<MazeAnalyst>(fname);
	}
	catch (const MazeError& e)
	{
		error_msg = e.what();
		return (false);
	}

	m->Explore();
	if (m->GetType() == AMazeAnalyst::e_imperfect)
	{
		return (true);
	}

	return (false);
}

typedef std::function<bool ()> Test;

int		main(int ac, char** av)
{
	if (ac != 3)
	{
		std::cout << "Missing Parameters." << std::endl;
		return (1);
	}

	std::unordered_map<std::string, Test>	tests = {
		{ "Format", [&av](){ return (RunTest_FORMAT(av[2], 10, 5)); } },
		{ "Wayout", [&av](){ return (RunTest_WAYOUT(av[2])); } },
		{ "Perfect", [&av](){ return (RunTest_ISPERFECT(av[2])); } },
		{ "RPerfect", [&av](){ return (RunTest_ISRPERFECT(av[2])); } },
		{ "RRPerfect", [&av](){ return (RunTest_ISRRPERFECT(av[2])); } },
		{ "Imperfect", [&av](){ return (RunTest_ISIMPERFECT(av[2])); } }
	};

	try
	{
		std::cout << std::boolalpha << tests[av[1]]() << std::endl;
		std::cout << error_msg << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "FATAL ERROR !: " << e.what() << std::endl;
		return (1);
	}

	return (0);
}
