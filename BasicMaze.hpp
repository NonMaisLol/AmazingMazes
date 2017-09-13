#ifndef		__BASICMAZE_HH__
#define		__BASICMAZE_HH__

#include	<iostream>
#include	<fstream>
#include	<string>
#include	<vector>

#include	"AMaze.hpp"

class		BasicMaze :
  public AMaze
{
private:
  char*		p_maze;
  
public:
  BasicMaze();
  BasicMaze(const BasicMaze& m);
  ~BasicMaze();

public:
  BasicMaze&	operator=(const BasicMaze& m);

public:
  void		PrintConsole() const;
  
public:
  char		GetElement(uint x, uint y) const;
  bool		SetElement(uint x, uint y, char e);
  bool		Load(const char* f);
  bool		Explore();
};

#endif		// __BASICMAZE_HH__
