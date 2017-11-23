#include	<iostream>
#include	<memory>

#include	"BasicMaze.hpp"

enum	eTest
{
	e_size,
	e_char,
	e_trailing
};

bool	Test(eTest test, const char* fname, uint w, uint h)
{
	try
	{
		auto m = std::make_unique<BasicMaze>(fname);

		m->Explore();
		m->PrintConsole();
	}
	catch (const AMaze::eError& e)
	{
		if (e == AMaze::eError::e_bad_file)
		{
			std::cout << "Bad  File" << std::endl;
		}
		else if (e == AMaze::eError::e_bad_file)
		{
			std::cout << "Not a Rectangle" << std::endl;
		}
		else if (e == AMaze::eError::e_alloc_failed)
		{
			std::cout << "Maze allocation failed" << std::endl;
		}
		else if (e == AMaze::eError::e_bad_char)
		{
			std::cout << "Bad Char" << std::endl;
		}
		else
		{
			std::cout << "Another error occurred !" << std::endl;
			return (false);
		}
	}
	return (true);
}

int		main(int ac, char** av)
{
  if (ac != 2)
  {
      std::cout << "Missing Parameters." << std::endl;
      return (1);
  }

  try
  {
	  if (Test(eTest::e_size, av[1], 10, 5) == false)
	  {
		  return (1);
	  }
  }
  catch (const std::exception& e)
  {
  	std::cout << "FATAL ERROR: " << e.what() << std::endl;
  	return (1);
  }

  return (0);
}
