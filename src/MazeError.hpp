/*
 * MazeError.hpp
 *
 *  Created on: Jan 3, 2018
 *      Author: Pascal Assens
 */

#ifndef 	__MAZEERROR__HPP__
#define 	__MAZEERROR__HPP__

#include	<exception>
#include	<iostream>

typedef		unsigned int	uint;

class 		MazeError :
public std::exception
{
public:
	enum	eError
	{
	  e_unknown,
	  e_bad_file,
	  e_not_a_rect,
	  e_alloc_failed,
	  e_bad_char,
	  e_trailing_error
	};

private:
	eError	p_type;

public:
	MazeError(const eError& e) throw();
	virtual ~MazeError() throw();

private:
	MazeError() : p_type(eError::e_unknown) { }

public:
	const eError	GetType() const throw() { return (this->p_type); }

public:
	const char*		what() const throw();
};

#endif 		/* __MAZEERROR__HPP__ */
