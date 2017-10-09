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
	if (this->p_loaded == false)
	{
		std::cout << "Not loaded." << std::endl;
		return ;
	}
	std::cout << "Width: " << this->p_width << std::endl;
	std::cout << "Height: " << this->p_height << std::endl;
	std::cout << "Size: " << this->p_size << std::endl;
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
	bool				LoadingIsOk;
	std::ifstream		ifs(f, std::ios::in);


	if (!ifs)
		return (false);
	
	LoadingIsOk = this->CheckFormat(ifs);
	if (LoadingIsOk == false)
	{
		ifs.close();
		return (false);
	}
	LoadingIsOk = this->RealLoading(ifs);
	ifs.close();
	this->p_loaded = LoadingIsOk;
	return (LoadingIsOk);
}

bool			BasicMaze::Explore()
{
	return (false);
}

bool			BasicMaze::CheckFormat(std::ifstream& ifs)
{
	bool			    first_line;
	std::string			line;

	first_line = true;
	this->p_height = 0;
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
		++this->p_height;
	}
	return (true);
}

bool			BasicMaze::RealLoading(std::ifstream& ifs)
{
	return (false);
}
