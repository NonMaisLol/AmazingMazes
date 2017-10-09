#include	"BasicMaze.hpp"

BasicMaze::BasicMaze()
{
}

BasicMaze::BasicMaze(const BasicMaze& m)
{
}

BasicMaze::~BasicMaze()
{
}

BasicMaze&		BasicMaze::operator=(const BasicMaze& m)
{
}

void			BasicMaze::PrintConsole() const
{
}

char			BasicMaze::GetElement(uint x, uint y) const
{
  return (0);
}

bool			BasicMaze::SetElement(uint x, uint y, char e)
{
  return (false);
}

bool			BasicMaze::Load(const char* f)
{
  std::ifstream		ifs(f, std::ios::in);
  bool			first_line;

  if (ifs)
    {
      std::string	line;

      first_line = true;
      this->p_length = 0;
      this->p_width = 0;
      while (std::getline(ifs, line))
	{
	  if (first_line == true)
	    {
	      this->p_width = line.size();
	      first_line = false;
	    }
	  else if (this->p_width != line.size())
	    {
	      return (false);
	    }
	  ++this->p_length;
	}
      ifs.close();
      return (true);
    }
  return (false);
}

bool			BasicMaze::Explore()
{
  return (false);
}
