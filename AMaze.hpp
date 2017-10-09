#ifndef		__AMAZE_HH__
#define		__AMAZE_HH__

/*
  Ctor par copie dans la fille a mettre aussi ici.
 */

typedef		unsigned int	uint;

class		AMaze
{
public:
  enum		eType
  {
    e_none,
    e_imperfect,
    e_perfect,
    e_rperfect,
    e_rrperfect
  };

public:
  AMaze();
  virtual ~AMaze() { }

protected:
  AMaze(const AMaze& m);
  AMaze&	operator=(const AMaze& m);
  
protected:
  bool		p_loaded;
  bool		p_explored;
  uint		p_length;
  uint		p_width;
  uint		p_size;
  uint		p_ntwist;
  uint		p_ndeadend;
  uint		p_nturn;
  eType		p_type;

public:
  bool		GetLoaded() const	{ return (this->p_loaded); }
  bool		GetExplored() const	{ return (this->p_explored); }
  uint		GetLength() const	{ return (this->p_length); }
  uint		GetWidth() const	{ return (this->p_width); }
  uint		GetSize() const		{ return (this->p_size); }
  uint		GetNTwist() const	{ return (this->p_ntwist); }
  uint		GetNDeadEnd() const	{ return (this->p_ndeadend); }
  uint		GetNTurn() const	{ return (this->p_nturn); }
  eType		GetType() const		{ return (this->p_type); }

public:
  virtual void	PrintConsole() const			= 0;
  
public:
  virtual char	GetElement(uint x, uint y) const	= 0;
  virtual bool	SetElement(uint x, uint y, char e)	= 0;
  virtual bool	Load(const char* f)			= 0;
  virtual bool	Explore()				= 0;
};

#endif		// __AMAZE_HH__
