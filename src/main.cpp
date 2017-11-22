#include	<iostream>

#include	"BasicMaze.hpp"

int		main(int ac, char** av)
{
  BasicMaze	m;

  if (ac != 2)
  {
      std::cout << "Missing Parameters." << std::endl;
      return (1);
  }
  if (m.Load(av[1]) == false)
  {
      std::cout << "Loading Failed." << std::endl;
      return (1);
  }
  if (m.Explore() == false)
  {
	  std::cout << "Cant Explore." << std::endl;
	  return (1);
  }
  m.PrintConsole();
  return (0);
}
