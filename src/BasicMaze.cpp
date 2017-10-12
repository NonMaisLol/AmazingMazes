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
	for (uint i = 0; i < this->p_size;)
	{
		write(1, (void*)(this->p_maze + i), this->p_width);
		std::cout << std::endl;
		i += this->GetWidth();
	}
}

char			BasicMaze::GetElement(uint x, uint y) const
{
	if (this->p_loaded == false)
		return (0);
	return (1);
}

bool			BasicMaze::SetElement(uint x, uint y, char e)
{
	if (this->p_loaded == false)
		return (false);
	return (true);
}

bool			BasicMaze::Load(const char* f)
{
	std::ifstream		ifs(f, std::ios::in);

	if (!ifs)
		return (false);
	
	this->p_loaded = false;
	if (this->CheckFormat(ifs) == false)
	{
		ifs.close();
		return (false);
	}
	if (this->RealLoading(ifs) == false)
	{
		ifs.close();
		return (false);
	}
	ifs.close();
	if(this->CheckCharacter(ifs) == false)
	{
		return (false);
	}
	this->p_loaded = true;

	return (true);
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
	this->p_size = this->p_width * this->p_height;
	return (true);
}

bool			BasicMaze::RealLoading(std::ifstream& ifs)
{
	std::string	line;
	uint		idx = 0;

	ifs.clear();
	ifs.seekg(0, std::ios::beg);
	this->p_maze = new char[this->p_size]();
	while (std::getline(ifs, line))
	{
		memcpy(this->p_maze + idx, line.c_str(), line.length());
		idx += line.length();
	}
	return (true);
}

bool			BasicMaze::CheckCharacter(std::ifstream& ifs)
{
	for (uint i = 0; i < this->p_size; ++i)
	{
		if (this->p_maze[i] != SHEB_EMPTY && this->p_maze[i] != SHEB_WALL)
		{
			return (false);
		}
	}
	return (true);
}
