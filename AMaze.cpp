#include	"AMaze.hpp"

AMaze::AMaze() :
  p_loaded(false), p_explored(false), p_length(0),
  p_width(0), p_size(0), p_ntwist(0), p_ndeadend(0),
  p_nturn(0), p_type(AMaze::eType::e_none)
{
}
