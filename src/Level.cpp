#include "Level.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <SDL.h>

#include "Utils.h"
#include "Camera.h"

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

void Level::drawWalls(SDL_Surface* surface, Camera* cam)
{
	//Haven't drawn anything yet
	for (unsigned i = 0; i < drawnSectors.size(); ++i) 
	{
		drawnSectors.at(i) = false;
	}

	Vector2 zdl = Utils::rotateVec(Vector2{ 0.0f, 1.0f }, +(cam->getFovRad() / 2.f));
	Vector2 zdr = Utils::rotateVec(Vector2{ 0.0f, 1.0f }, -(cam->getFovRad() / 2.f));
	Vector2 zNearLeft{ zdl.x * Z_NEAR, zdl.y * Z_NEAR };
	Vector2 zNearRight{ zdr.x * Z_NEAR, zdr.y * Z_NEAR };
	Vector2 zFarLeft{ zdl.x * Z_FAR, zdl.y * Z_FAR };
	Vector2 zFarRight{ zdr.x * Z_FAR, zdr.y * Z_FAR };

	Vector2 pos1 = cam->convertCoords(lines.at(0).getStart());
	Vector2 pos2 = cam->convertCoords(lines.at(0).getEnd());

	Vector2 clipPos1 = pos1;
	Vector2 clipPos2 = pos2;

	if (clipPos1.y <= 0 && clipPos2.y <= 0) //Is wall behind player?
	{
		return;
	}

	float apos1 = Utils::normalizeAngle(atan2f(clipPos1.y, clipPos1.x) - (PI / 2));
	float apos2 = Utils::normalizeAngle(atan2f(clipPos2.y, clipPos2.x) - (PI / 2));

	if (clipPos1.y < Z_NEAR || clipPos2.y < Z_NEAR || apos1 > +(cam->getFovRad() / 2) || apos2 < -(cam->getFovRad() / 2)) 
	{
		Vector2 interLeft = Utils::intersectLines(clipPos1, clipPos2, zNearLeft, zFarLeft);
		Vector2 interRight = Utils::intersectLines(clipPos1, clipPos2, zNearRight, zFarRight);

		if (!isnan(interLeft.x)) 
		{
			clipPos1 = interLeft;
			apos1 = Utils::normalizeAngle(atan2f(clipPos1.y, clipPos1.x) - (PI / 2));
		}

		if (!isnan(interRight.x)) 
		{
			clipPos2 = interRight;
			apos2 = Utils::normalizeAngle(atan2f(clipPos2.y, clipPos2.x) - (PI / 2));
		}
	}

	if (apos1 < apos2) //Wrong side
	{
		return;
	}	

	if ((apos1 < -(cam->getFovRad() / 2) && apos2 < -(cam->getFovRad() / 2)) ||
		(apos1 > +(cam->getFovRad() / 2) && apos2 > +(cam->getFovRad() / 2))) 
	{
		return;
	}

	int tx1 = cam->screenAngleToX(apos1, 640);
	int tx2 = cam->screenAngleToX(apos2, 640);

	int x1 = SDL_clamp(tx1, 0, 640 - 1);
	int x2 = SDL_clamp(tx2, 0, 640 - 1);

	float zfloor = 0.0f;
	float zceil = 4.0f;

	float scaleY1 = (0.5 * 360) / clipPos1.y;

	if (isnan(scaleY1)) 
	{
		scaleY1 = 1e10;
	}

	float scaleY2 = (0.5 * 360) / clipPos2.y;

	if (isnan(scaleY2))
	{
		scaleY2 = 1e10;
	}

	int yFloor1 = (640 / 2) + (int)((zfloor - cam->getHeight()) * scaleY1);
	int yFloor2 = (640 / 2) + (int)((zfloor - cam->getHeight()) * scaleY2);
	int yCeil1 = (640 / 2) + (int)((zceil - cam->getHeight()) * scaleY1);
	int yCeil2 = (640 / 2) + (int)((zceil - cam->getHeight()) * scaleY2);

	for (int x = x1; x <= x2; ++x) 
	{
		float xProg = (x - tx1) / (float)(tx1 - tx2);
		if (isnan(xProg)) 
		{
			xProg = 0;
		}

		int tYFloor = (int)(xProg * (yFloor2 - yFloor1)) + yFloor1;
		int tYCeil = (int)(xProg * (yCeil2 - yCeil1)) + yCeil1;

		int yFloor = SDL_clamp(tYFloor, 0, 360 - 1);
		int yCeil = SDL_clamp(tYCeil, 0, 360 - 1);

		Utils::drawVertLineColor(surface, x, yFloor, yCeil, 0xff0000ff);
	}
}
