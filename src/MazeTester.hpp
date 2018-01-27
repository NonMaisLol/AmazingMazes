/*
 * MazeTester.hpp
 *
 *  Created on: Jan 27, 2018
 *      Author: Pascal Assens
 */

#ifndef 	__MAZETESTER_HPP__
#define 	__MAZETESTER_HPP__

#include	<memory>
#include	<string>
#include	<unordered_map>
#include	<functional>

#include	"MazeAnalyst.hpp"

typedef		std::function<bool ()> Test;

class 		MazeTester
{
public:
	enum	eTest
	{
		e_none,
		e_format,
		e_wayout,
		e_perfect,
		e_rperfect,
		e_rrperfect,
		e_imperfect
	};

private:
	std::string		p_message;

public:
	MazeTester();
	~MazeTester();

public:
	const std::string&	GetMessage() const { return (this->p_message); }

public:
	bool		RunTest(const char* fname, uint w, uint h, MazeTester::eTest t);

private:
	bool		RunTest_FORMAT(std::unique_ptr<AMazeAnalyst>& m, uint w, uint h);
	bool		RunTest_WAYOUT(std::unique_ptr<AMazeAnalyst>& m);
	bool		RunTest_ISPERFECT(std::unique_ptr<AMazeAnalyst>& m);
	bool		RunTest_ISRPERFECT(std::unique_ptr<AMazeAnalyst>& m);
	bool		RunTest_ISRRPERFECT(std::unique_ptr<AMazeAnalyst>& m);
	bool		RunTest_ISIMPERFECT(std::unique_ptr<AMazeAnalyst>& m);
};

#endif /* __MAZETESTER_HPP__ */
