#include "Level.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <SDL.h>

Level::Level()
{

}

Level::~Level()
{

}

int Level::loadLevel(std::string filepath)
{
	std::ifstream file;

	file.open(filepath);

	if (!file.is_open()) 
	{
		return 1;
	}

	unsigned int state = READ_LINES;

	std::string fileline;

	while (!file.eof()) 
	{
		//Filter out commented lines and blank lines
		if (file.peek() == '#' || file.peek() == '\n')
		{
			std::getline(file, fileline);
			fileline = ""; //Throw out line
			continue;
		}
		else if (file.peek() == '[') //Change what data is being read
		{
			file.get();
			std::getline(file, fileline, ']');
			if (fileline == "sectors") 
			{
				state = READ_SECTORS;
			}
			else if (fileline == "lines") 
			{
				state = READ_LINES;
			}
			continue;
		}

		if (state == READ_LINES)
		{
			Vector2 startpos = {0,0};
			Vector2 endpos = {0,0};
			int portalnum = 0;

			for (char i = 0; i < 5; ++i)
			{
				getline(file, fileline, ',');

				switch (i)
				{
				case 0:
					startpos.x = std::stof(fileline);
					break;
				case 1:
					startpos.y = std::stof(fileline);
					break;
				case 2:
					endpos.x = std::stof(fileline);
					break;
				case 3:
					endpos.y = std::stof(fileline);
					break;
				case 4:
					portalnum = std::stoi(fileline);
					break;
				}
			}

			lines.push_back(Line(startpos, endpos, portalnum));
		}
		else if (state == READ_SECTORS) 
		{
			uint32_t secid = 0;
			float flHeight = 0;
			float ceilHeight = 0;
			uint32_t fwall = 0;
			uint32_t nwalls = 0;

			for (char i = 0; i < 5; ++i) 
			{
				getline(file, fileline, ',');

				switch (i)
				{
				case 0:
					secid = std::stoi(fileline);
					break;
				case 1:
					fwall = std::stoi(fileline);
					break;
				case 2:
					nwalls = std::stoi(fileline);
					break;
				case 3:
					flHeight = std::stof(fileline);
					break;
				case 4:
					ceilHeight = std::stof(fileline);
					break;
				}
			}

			sectors.push_back(Sector(secid, flHeight, ceilHeight, fwall, nwalls));
			drawnSectors.push_back(false);
		}
		file.peek();
	}

	//std::cout << sectors.size() << " " << drawnSectors.size() << " " << lines.size() << "\n";
	//for (unsigned i = 0; i < lines.size(); ++i) 
	//{
	//	lines.at(i).printPositions();
	//}

	file.close();

	return 0; //Success
}
