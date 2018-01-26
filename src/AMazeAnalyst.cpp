/*
 * AMazeAnalyst.cpp
 *
 *  Created on: Jan 3, 2018
 *      Author: Pascal Assens
 */

#include	"AMazeAnalyst.hpp"

AMazeAnalyst::AMazeAnalyst() :
  p_height(0), p_width(0), p_size(0), p_npath(0), p_ntwist(0),
  p_ndeadend(0), p_nturn(0), p_wayout(false),
  p_type(AMazeAnalyst::e_none)
{

}

AMazeAnalyst&			AMazeAnalyst::operator=(const AMazeAnalyst& m)
{
	return (*this);
}
