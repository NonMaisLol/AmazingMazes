#include	<iostream>

#include	"BasicMaze.hpp"

int		main(int ac, char** av)
{
  BasicMaze	m;

  if (ac != 2)
    {
      std::cout << "Missing Parameters." << std::endl;
      return (0);
    }
  if (m.Load(av[1]) == false)
    {
      std::cout << "Loading Failed." << std::endl;
    }
  m.PrintConsole();
  return (0);
}
