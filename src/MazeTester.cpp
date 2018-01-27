/*
 * MazeTester.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: Pascal Assens
 */

#include 	"MazeTester.hpp"

MazeTester::MazeTester() :
p_message("")
{

}

MazeTester::~MazeTester()
{

}

bool		MazeTester::RunTest(const char* fname, uint w, uint h, MazeTester::eTest t)
{
	std::unique_ptr<AMazeAnalyst>						m;
	static std::unordered_map<MazeTester::eTest, Test>	tests = {
			{ MazeTester::e_format, [this, &m, &w, &h](){ return (this->RunTest_FORMAT(m, w, h)); } },
			{ MazeTester::e_wayout, [this, &m](){ return (this->RunTest_WAYOUT(m)); } },
			{ MazeTester::e_perfect, [this, &m](){ return (this->RunTest_ISPERFECT(m)); } },
			{ MazeTester::e_rperfect, [this, &m](){ return (this->RunTest_ISRPERFECT(m)); } },
			{ MazeTester::e_rrperfect, [this, &m](){ return (this->RunTest_ISRRPERFECT(m)); } },
			{ MazeTester::e_imperfect, [this, &m](){ return (this->RunTest_ISIMPERFECT(m)); } }
	};

	try
	{
		m = std::make_unique<MazeAnalyst>(fname);
	}
	catch (const MazeError& e)
	{
		this->p_message = e.what();
		return (false);
	}

	if (t != MazeTester::e_format && tests[MazeTester::e_format]() == false)
	{
		return (false);
	}

	return (tests[t]());
}

bool		MazeTester::RunTest_FORMAT(std::unique_ptr<AMazeAnalyst>& m, uint w, uint h)
{
	if (m->GetWidth() != w || m->GetHeight() != h)
	{
		this->p_message = "Size is such wrong !";
		return (false);
	}
	return (true);
}

bool		MazeTester::RunTest_WAYOUT(std::unique_ptr<AMazeAnalyst>& m)
{
	m->Explore();
	if (m->GetWayOut() == true)
	{
		return (true);
	}
	return (false);
}

bool		MazeTester::RunTest_ISPERFECT(std::unique_ptr<AMazeAnalyst>& m)
{
	m->Explore();
	if (m->GetType() == AMazeAnalyst::e_perfect ||
		m->GetType() == AMazeAnalyst::e_rperfect ||
		m->GetType() == AMazeAnalyst::e_rrperfect)
	{
		return (true);
	}
	return (false);
}

bool		MazeTester::RunTest_ISRPERFECT(std::unique_ptr<AMazeAnalyst>& m)
{
	m->Explore();
	if (m->GetType() == AMazeAnalyst::e_rperfect ||
		m->GetType() == AMazeAnalyst::e_rrperfect)
	{
		return (true);
	}
	return (false);
}

bool		MazeTester::RunTest_ISRRPERFECT(std::unique_ptr<AMazeAnalyst>& m)
{
	m->Explore();
	if (m->GetType() == AMazeAnalyst::e_rrperfect)
	{
		return (true);
	}
	return (false);
}

bool		MazeTester::RunTest_ISIMPERFECT(std::unique_ptr<AMazeAnalyst>& m)
{
	m->Explore();
	if (m->GetType() == AMazeAnalyst::e_imperfect)
	{
		return (true);
	}
	return (false);
}

