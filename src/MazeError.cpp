/*
 * MazeError.cpp
 *
 *  Created on: Jan 3, 2018
 *      Author: Pascal Assens
 */

#include "MazeError.hpp"

MazeError::MazeError(const eError& e) throw() :
	p_type(e)
{

}

MazeError::~MazeError() throw()
{

}

const char*			MazeError::what() const throw()
{
	switch (this->p_type)
	{
	case (eError::e_bad_file) :
		return ("Bad File.");
		break ;
	case (eError::e_not_a_rect) :
		return ("Not a Rectangle.");
		break ;
	case (eError::e_alloc_failed) :
		return ("Maze allocation failed.");
		break ;
	case (eError::e_bad_char) :
		return ("Bad Char.");
		break;
	case (eError::e_trailing_error) :
		return ("Trailing Error");
		break ;
	default:
		return ("Another error occurred !");
		break ;
	}
}
