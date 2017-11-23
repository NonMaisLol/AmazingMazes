#ifndef		__BASICMAZE_HH__
#define		__BASICMAZE_HH__

#include	<iostream>
#include	<fstream>
#include	<string>
#include	<string.h>
#include	<vector>
#include	<unistd.h>
#include	<memory>

#include	"AMaze.hpp"

class		BasicMaze :
public AMaze
{
private:
	std::unique_ptr<char[]>	p_maze;
  
public:
	BasicMaze(const char* fname);
	BasicMaze(const BasicMaze& m);
	~BasicMaze();

private:
	BasicMaze() { }

public:
  BasicMaze&	operator=(const BasicMaze& m);

public:
  void		PrintConsole() const;
  
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

#endif		// __BASICMAZE_HH__
