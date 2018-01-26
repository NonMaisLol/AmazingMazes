/*
 * AMazeAnalyst.hpp
 *
 *  Created on: Jan 3, 2018
 *      Author: Pascal Assens
 */

#ifndef		__AMAZEANALYST_HPP__
#define		__AMAZEANALYST_HPP__

#include	<memory>
#include	<string>
#include	<unistd.h>

#include	"MazeError.hpp"

#define		SHEB_EMPTY		'*'
#define		SHEB_WALL		'X'
#define		SHEB_EXPLORED	'e'

typedef		unsigned int	uint;

class		AMazeAnalyst
{
public:
  enum		eType
  {
    e_none,			// Nothing
    e_imperfect,	// Imperfect Maze
    e_perfect,		// Perfect Maze
    e_rperfect,		// Really Perfect Maze
    e_rrperfect		// Really REALLY Perfect Maze
  };

protected:
  uint		p_height;
  uint		p_width;
  uint		p_size;
  uint		p_npath;
  uint		p_ntwist;
  uint		p_ndeadend;
  uint		p_nturn;
  bool		p_wayout;
  eType		p_type;

protected:
  AMazeAnalyst();
  AMazeAnalyst&	operator=(const AMazeAnalyst& m);

public:
  virtual ~AMazeAnalyst() { }

public:
  uint		GetHeight() const	{ return (this->p_height); }
  uint		GetWidth() const	{ return (this->p_width); }
  uint		GetSize() const		{ return (this->p_size); }
  uint		GetNPath() const	{ return (this->p_npath); }
  uint		GetNTwist() const	{ return (this->p_ntwist); }
  uint		GetNDeadEnd() const	{ return (this->p_ndeadend); }
  uint		GetNTurn() const	{ return (this->p_nturn); }
  bool		GetWayOut() const	{ return (this->p_wayout); }
  eType		GetType() const		{ return (this->p_type); }

public:
  virtual std::string	ToString() const				= 0;
  virtual std::string	ToJson() const					= 0;
  
public:
  virtual char	GetElement(uint x, uint y) const		= 0;
  virtual bool	SetElement(uint x, uint y, char e)		= 0;
  virtual bool	Explore()								= 0;
};

#endif		// __AMAZEANALYST_HH__
