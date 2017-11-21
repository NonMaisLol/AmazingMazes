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
	return (*this);
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
	std::cout << "Path: " << this->p_npath << std::endl;
	std::cout << "Twists: " << this->p_ntwist << std::endl;
	std::cout << "NDeadEnds: " << this->p_ndeadend << std::endl;
	std::cout << "Turns: " << this->p_nturn << std::endl;
	if (this->p_type == AMaze::eType::e_imperfect)
		std::cout << "Imperfect Maze" << std::endl;
	else if (this->p_type == AMaze::eType::e_perfect)
		std::cout << "Perfect Maze" << std::endl;
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

	if (x >= this->p_width || y >= this->p_height)
		return (0);

	return (this->p_maze[y * this->p_width + x]);
}

bool			BasicMaze::SetElement(uint x, uint y, char e)
{
	if (this->p_loaded == false)
		return (false);

	if (x >= this->p_width || y >= this->p_height)
		return (false);

	this->p_maze[y * this->p_width + x] = e;
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
	if (this->p_loaded == false)
		return (false);

	this->p_type = AMaze::eType::e_perfect;
	this->Track(0, 0);

	return (true);
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

char			BasicMaze::Track(uint x, uint y)
{
	uint		dirT[4][2] = {
			{x + 1, y},
			{x - 1, y},
			{x, y + 1},
			{x, y - 1}
	};
	char		nex;
	char		walls = 0;
	char		vertical = 0;
	char		horizontal = 0;
	char		explored = 0;

	if (this->GetElement(x, y) != SHEB_EMPTY)
		return (this->GetElement(x, y));

	this->SetElement(x, y, SHEB_EXPLORED);
	++this->p_npath;

	for (uint i = 0; i < 4; ++i)
	{
		nex = this->Track(dirT[i][0], dirT[i][1]);
		if (nex == SHEB_EXPLORED)
			++explored;
		if (nex == SHEB_WALL || nex == 0)
		{
			++walls;
			if (i == 0 || i == 1)
				++vertical;
			else
				++horizontal;
		}
	}

	if (walls == 3 || walls == 4)
		++this->p_ndeadend;
	else if (walls == 0 || walls == 1)
		++this->p_ntwist;
	else if (walls == 2 && vertical == 1)
		++this->p_nturn;

	if (explored > 1)
		this->p_type = AMaze::eType::e_imperfect;

	return (SHEB_EMPTY);
}
