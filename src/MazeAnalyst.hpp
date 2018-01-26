/*
 * MazeAnalyst.hpp
 *
 *  Created on: Jan 3, 2018
 *      Author: Pascal Assens
 */

#ifndef		__MAZEANALYST_HPP__
#define		__MAZEANALYST_HPP__

#include	<iostream>
#include	<fstream>
#include	<string>
#include	<string.h>
#include	<vector>
#include	<unistd.h>
#include	<memory>
#include	<sstream>

#include 	"AMazeAnalyst.hpp"

class		MazeAnalyst :
public AMazeAnalyst
{
private:
	std::unique_ptr<char[]>	p_maze;
  
public:
	MazeAnalyst(const char* fname);
	MazeAnalyst(const MazeAnalyst& m);
	~MazeAnalyst();

private:
	MazeAnalyst() { }

public:
	MazeAnalyst&	operator=(const MazeAnalyst& m);

public:
  std::string		ToString() const;
  std::string		ToJson() const;
  
public:
  char		GetElement(uint x, uint y) const;
  bool		SetElement(uint x, uint y, char e);
  bool		Explore();

protected:
  bool		Load(const char* f);
  bool		CheckFormat(std::ifstream& ifs);
  bool		RealLoading(std::ifstream& ifs);
  bool		CheckCharacter(std::ifstream& ifs);
  char		Track(uint x, uint y);
  void		CheckForPerfection();
};

#endif		// __MAZEANALYST_HPP__
