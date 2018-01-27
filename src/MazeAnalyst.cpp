/*
 * MazeAnalyst.cpp
 *
 *  Created on: Jan 3, 2018
 *      Author: Pascal Assens
 */

#include	"MazeAnalyst.hpp"

MazeAnalyst::MazeAnalyst(const char* filename) :
	p_maze(nullptr)
{
	this->Load(filename);
}

MazeAnalyst::MazeAnalyst(const MazeAnalyst& m)
{

}

MazeAnalyst::~MazeAnalyst()
{

}

MazeAnalyst&	MazeAnalyst::operator=(const MazeAnalyst& m)
{
	return (*this);
}

std::string		MazeAnalyst::ToString() const
{
	std::stringstream			out;

	out << "Width: " << this->p_width << std::endl;
	out << "Height: " << this->p_height << std::endl;
	out << "Size: " << this->p_size << std::endl;
	out << "Path: " << this->p_npath << std::endl;
	out << "Twists: " << this->p_ntwist << std::endl;
	out << "NDeadEnds: " << this->p_ndeadend << std::endl;
	out << "Turns: " << this->p_nturn << std::endl;
	out << "WayOut: " << std::boolalpha << this->p_wayout << std::endl;
	if (this->p_type == AMazeAnalyst::e_imperfect)
		out << "Imperfect Maze" << std::endl;
	else if (this->p_type == AMazeAnalyst::e_perfect)
		out << "Perfect Maze" << std::endl;
	else if (this->p_type == AMazeAnalyst::e_rperfect)
		out << "R Perfect Maze" << std::endl;
	else if (this->p_type == AMazeAnalyst::e_rrperfect)
		out << "R R Perfect Maze" << std::endl;
	else
		out << "NONE" << std::endl;

	for (uint i = 0; i < this->p_size;)
	{
		out.write((this->p_maze.get() + i), this->p_width);
		out << std::endl;
		i += this->GetWidth();
	}

	return (out.str().c_str());
}

std::string		MazeAnalyst::ToJson() const
{
	std::stringstream		out;

	out << "{" << std::endl;
	out << '\t' << "\"Width\": " << this->p_width << "," << std::endl;
	out << '\t' << "\"Height\": " << this->p_height << "," << std::endl;
	out << '\t' << "\"Size\": " << this->p_size << "," << std::endl;
	out << '\t' << "\"Path\": " << this->p_npath << "," << std::endl;
	out << '\t' << "\"Twists\": " << this->p_ntwist << "," << std::endl;
	out << '\t' << "\"DeadEnds\": " << this->p_ndeadend << "," << std::endl;
	out << '\t' << "\"Turns\": " << this->p_nturn << "," << std::endl;
	out << '\t' << "\"WayOut\": " << this->p_wayout << "," << std::endl;
	if (this->p_type == AMazeAnalyst::e_imperfect)
		out << "\t"<< "\"Type\": IMPERFECT" << std::endl;
	else if (this->p_type == AMazeAnalyst::e_perfect)
		out << "\t"<< "\"Type\": PERFECT" << std::endl;
	else if (this->p_type == AMazeAnalyst::e_rperfect)
		out << "\t"<< "\"Type\": RPERFECT" << std::endl;
	else if (this->p_type == AMazeAnalyst::e_rrperfect)
		out << "\t"<< "\"Type\": RRPERFECT" << std::endl;
	else
		out << "\t"<< "\"Type\": NONE" << std::endl;
	out << "}";

	return (out.str().c_str());
}

char			MazeAnalyst::GetElement(uint x, uint y) const
{
	if (x >= this->p_width || y >= this->p_height)
		return (0);

	return (this->p_maze[y * this->p_width + x]);
}

bool			MazeAnalyst::SetElement(uint x, uint y, char e)
{
	if (x >= this->p_width || y >= this->p_height)
		return (false);

	this->p_maze[y * this->p_width + x] = e;
	return (true);
}

bool			MazeAnalyst::Explore()
{
	if (this->Track(0, 0) != SHEB_EMPTY)
		return (false);

	this->CheckForPerfection();

	if (this->GetElement(0, 0) == SHEB_EXPLORED &&
			this->GetElement(this->p_width - 1, this->p_height - 1) == SHEB_EXPLORED)
	{
		this->p_wayout = true;
	}

	return (true);
}

bool			MazeAnalyst::Load(const char* f)
{
	std::ifstream		ifs(f, std::ios::in | std::ios::binary);

	if (!ifs)
		throw (MazeError(MazeError::e_bad_file));

	if (this->CheckFormat(ifs) == false)
	{
		ifs.close();
		throw (MazeError(MazeError::e_not_a_rect));
	}
	else if (this->RealLoading(ifs) == false)
	{
		ifs.close();
		throw (MazeError(MazeError::e_alloc_failed));
	}
	else if (this->CheckCharacter(ifs) == false)
	{
		ifs.close();
		throw (MazeError(MazeError::e_bad_char));
	}
	else if (this->CheckTrailing(ifs) == false)
	{
		ifs.close();
		throw (MazeError(MazeError::e_trailing_error));
	}
	ifs.close();
	return (true);
}

bool			MazeAnalyst::CheckFormat(std::ifstream& ifs)
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

bool			MazeAnalyst::RealLoading(std::ifstream& ifs)
{
	std::string	line;
	uint		idx = 0;

	ifs.clear();
	ifs.seekg(0, std::ios::beg);
	try
	{
		this->p_maze = std::make_unique<char[]>(this->p_size);
	}
	catch (const std::exception& e)
	{
		return (false);
	}
	while (std::getline(ifs, line))
	{
		memcpy(this->p_maze.get() + idx, line.c_str(), line.length());
		idx += line.length();
	}
	return (true);
}

bool			MazeAnalyst::CheckCharacter(std::ifstream& ifs)
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

bool			MazeAnalyst::CheckTrailing(std::ifstream& ifs)
{
	std::streampos fsize = 0;

	ifs.clear();
	ifs.seekg(0, std::ios::beg);
	fsize = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	fsize = ifs.tellg() - fsize;
	if (fsize != (((this->p_width + 1) * this->p_height) - 1))
	{
		return (false);
	}
	return (true);
}

char			MazeAnalyst::Track(uint x, uint y)
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
		}
	}

	if (walls == 3 || walls == 4)
		++this->p_ndeadend;
	else if (walls == 0 || walls == 1)
		++this->p_ntwist;
	else if (walls == 2 && vertical == 1)
		++this->p_nturn;

	if (explored > 1)
		this->p_type = AMazeAnalyst::e_imperfect;

	return (SHEB_EMPTY);
}

void			MazeAnalyst::CheckForPerfection()
{
	int			dirT[4][2] = {
			{1, 0}, {-1, 0},
			{0, 1}, {0, -1}
	};
	uint		walls = 0;
	char		val;

	if (this->p_type == AMazeAnalyst::e_imperfect)
		return ;

	this->p_type = AMazeAnalyst::e_rrperfect;
	for (uint y = 0; y < this->p_height; ++y)
	{
		for (uint x = 0; x < this->p_width; ++x)
		{
			walls = 0;
			if (this->GetElement(x, y) == SHEB_WALL)
			{
				for (uint i = 0; i < 4; ++i)
				{
					val = GetElement(x + dirT[i][0], y + dirT[i][1]);
					if (val == SHEB_EMPTY)
					{
						this->p_type = AMazeAnalyst::e_imperfect;
						return ;
					}
					if (val == SHEB_WALL || val == 0)
						++walls;
				}
			}
			if (walls == 4)
			{
				this->p_type = AMazeAnalyst::e_perfect;
				return ;
			}
			else if (walls == 3)
			{
				this->p_type = AMazeAnalyst::e_rperfect;
			}
		}
	}
}

