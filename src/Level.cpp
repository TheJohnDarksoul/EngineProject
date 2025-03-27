#include "Level.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <SDL.h>
#include <queue>

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
		char ch = file.peek();
		if (ch == '#' || ch == '\n')
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
			std::vector<uint32_t> iWalls;
			uint32_t nwalls = 0;

			for (char i = 0; i < 4; ++i) 
			{
				getline(file, fileline, ',');

				switch (i)
				{
				case 0:
					secid = std::stoi(fileline);
					break;
				case 1:
					flHeight = std::stof(fileline);
					break;
				case 2:
					ceilHeight = std::stof(fileline);
					break;
				case 3:
					nwalls = std::stoul(fileline);
					iWalls.assign(nwalls, 0);
					break;
				}
			}

			for (uint32_t i = 0; i < nwalls; ++i) 
			{
				getline(file, fileline, ',');

				iWalls.at(i) = std::stoul(fileline);
			}

			sectors.push_back(Sector(secid, flHeight, ceilHeight, &iWalls));
			drawnSectors.push_back(false);
		}
		file.peek();
	}

	file.close();

	for (unsigned i = 0; i < sectors.size(); ++i) 
	{
		for (unsigned j = 0; j < sectors.at(i).getWallIndices()->size(); ++j) 
		{
			std::cout << "x1: " << lines.at(j).getStart().x << " y1: " << lines.at(j).getStart().y
				<< " x2: " << lines.at(j).getEnd().x << " y2: " << lines.at(j).getEnd().y << "\n\n";
		}
	}

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

	float scaleY1 = (cam->getVFov() * 360) / clipPos1.y;

	if (isnan(scaleY1)) 
	{
		scaleY1 = 1e10;
	}

	float scaleY2 = (cam->getVFov() * 360) / clipPos2.y;

	if (isnan(scaleY2))
	{
		scaleY2 = 1e10;
	}

	#define EYE_Z 1.6f

	int yFloor1 = (640 / 2) + (int)((zfloor - EYE_Z) * scaleY1);
	int yFloor2 = (640 / 2) + (int)((zfloor - EYE_Z) * scaleY2);
	int yCeil1 = (640 / 2) + (int)((zceil - EYE_Z) * scaleY1);
	int yCeil2 = (640 / 2) + (int)((zceil - EYE_Z) * scaleY2);

	for (int x = x1; x <= x2; ++x) 
	{
		float xProg = (x - tx1) / (float)(tx2 - tx1);
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

void Level::drawLevel(SDL_Surface* surface, Camera* cam)
{
	//std::queue<Sector*> q;

	//From tutorial, change this later
	struct { int sectorno, sx1, sx2; } now = { cam->getSectorNum(), 0, surface->w - 1 };

	std::vector<int> ytop;
	ytop.assign(surface->w, 0);

	std::vector<int> ybottom;

	Vector2 camPos = cam->getPosition();
	
	for (unsigned x = 0; x < surface->w; ++x) 
	{
		ybottom.push_back(surface->h - 1);
	}

	for (unsigned i = 0; i < drawnSectors.size(); ++i) 
	{
		drawnSectors.at(i) = false;
	}

	Sector* sec = &sectors.at(now.sectorno);

	for (unsigned i = 0; i < sec->getNumWalls(); ++i) 
	{
		//Get x,y coords and put them in camera view
		float vx1 = lines.at(sec->getWallIndices()->at(i)).getStart().x - camPos.x;
		float vy1 = lines.at(sec->getWallIndices()->at(i)).getStart().y - camPos.y;

		float vx2 = lines.at(sec->getWallIndices()->at(i)).getEnd().x - camPos.x;
		float vy2 = lines.at(sec->getWallIndices()->at(i)).getEnd().y - camPos.y;

		//Rotate points around camera view
		float camCos = cosf(Utils::degToRad(cam->getAngle()));
		float camSin = sinf(Utils::degToRad(cam->getAngle()));

		float tx1 = vx1 * camSin - vy1 * camCos;
		float tz1 = vx1 * camCos + vy1 * camSin;

		float tx2 = vx2 * camSin - vy2 * camCos;
		float tz2 = vx2 * camCos + vy2 * camSin;

		//Is wall at least partially visable?
		if (tz1 <= 0.f && tz2 <= 0.f) 
		{
			continue;
		}

		//If partially behind camera, clip it against view
		if (tz1 <= 0.f || tz2 <= 0.f) 
		{
			float nearz = 1e-4f;
			float farz = 5.f;
			float nearside = 1e-5f;
			float farside = 20.f;

			//Vector2 intersect1 = Utils::intersectLines(Vector2{ tx1, tz1 }, Vector2{ tx2, tz2 },
			//	Vector2{ -nearside, nearz }, Vector2{ -farside, farz });
			Vector2 intersect1 = Utils::intersectLines(tx1, tz1, tx2, tz2, -nearside, nearz, -farside, farz);
			//Vector2 intersect2 = Utils::intersectLines(Vector2{ tx1, tz1 }, Vector2{ tx2, tz2 },
			//	Vector2{ nearside, nearz }, Vector2{ farside, farz });
			Vector2 intersect2 = Utils::intersectLines(tx1, tz1, tx2, tz2, nearside, nearz, farside, farz);

			if (tz1 < nearz) 
			{
				if (intersect1.y > 0) 
				{
					tx1 = intersect1.x;
					tz1 = intersect1.y;
				}
				else 
				{
					tx1 = intersect2.x;
					tz1 = intersect2.y;
				}
			}
			if (tz2 < nearz) 
			{
				if (intersect1.y > 0) 
				{
					tx2 = intersect1.x;
					tz2 = intersect1.y;
				}
				else 
				{
					tx2 = intersect2.x;
					tz2 = intersect2.y;
				}
			}
		}

		//Do transformation

		//testing
		float hfov = surface->h * 0.73f;
		float vfov = surface->h * 0.2f;

		float xscale1 = hfov / tz1;
		float yscale1 = vfov / tz1;

		int x1 = surface->w / 2 - (int)(tx1 * xscale1);

		float xscale2 = hfov / tz2;
		float yscale2 = vfov / tz2;

		int x2 = surface->w / 2 - (int)(tx2 * xscale2);

		//Only render if visible
		if (x1 >= x2 || x2 < now.sx1 || x1 > now.sx2) 
		{
			continue;
		}

		//Get floor and ceiling heights relative to player view
		float yceil = sec->getCeilingHeight() - cam->getHeight();
		float yfloor = sec->getFloorHeight() - cam->getHeight();

		//Floor and ceiling coords to screen coords
		int y1a = surface->h / 2 - (int)(yceil * yscale1);
		int y1b = surface->h / 2 - (int)(yfloor * yscale1);

		//neighbors

		int y2a = surface->h / 2 - (int)(yceil * yscale2);
		int y2b = surface->h / 2 - (int)(yfloor * yscale2);

		//Actually render the wall
		int beginx = SDL_max(x1, now.sx1);
		int endx = SDL_min(x2, now.sx2);

		for (unsigned x = beginx; x <= endx; ++x) 
		{
			//Get y coords for floor and ceiling at x and clamp
			//top
			int ya = (x - x1) * (y2a - y1a) / (x2 - x1) + y1a;
			int cya = SDL_clamp(ya, ytop.at(x), ybottom.at(x));

			//bottom
			int yb = (x - x1) * (y2b - y1b) / (x2 - x1) + y1b;
			int cyb = SDL_clamp(yb, ytop.at(x), ybottom.at(x));

			//Utils::drawVertLineColors(surface, x, ytop.at(x), cya - 1, 0xff0000ff, 0x000000ff, 0x000000ff);

			//Utils::drawVertLineColors(surface, x, cyb + 1, ybottom.at(x), 0x0000ffff, 0x000000ff, 0x000000ff);

			//if neighbor..
			//else
			Utils::drawVertLineColors(surface, x, cya, cyb, 0xff0000ff, 0xff00ff00, 0xffff0000);
			//Utils::drawVertLineColor(surface, x, cya, cyb, 0xb2b2ffff);
		}
	}
}

void Level::render2d(SDL_Renderer* renderer, SDL_Color color)
{
	//Renders by looping through index list in sectors, less efficient than drawing lines directly, but will help pinpoint screwups
	for (unsigned i = 0; i < sectors.size(); ++i) 
	{
		for (unsigned j = 0; j < sectors.at(i).getNumWalls(); ++j)
		{
			lines.at(sectors.at(i).getWallIndices()->at(j)).render2d(renderer, color);
		}
	}
}

void Level::render(SDL_Renderer* renderer, Camera* cam)
{
	//Testing
	#define W 640
	#define H 360

	Sector* sec = &sectors.at(cam->getSectorNum());
	for (unsigned i = 0; i < sec->getNumWalls(); ++i) 
	{
		Line* lin = &lines.at(sec->getWallIndices()->at(i));

		Vector2 p1 = lin->getStart();
		Vector2 p2 = lin->getEnd();

		float ceilingHeight = -sec->getCeilingHeight();
		float floorHeight = -sec->getFloorHeight();

		float angleRad = Utils::degToRad(cam->getAngle());

		float distX1 = p1.x - cam->getPosition().x;
		float distY1 = p1.y - cam->getPosition().y;

		float distX2 = p2.x - cam->getPosition().x;
		float distY2 = p2.y - cam->getPosition().y;

		float z1 = distX1 * cosf(angleRad) + distY1 * sinf(angleRad);
		float z2 = distX2 * cosf(angleRad) + distY2 * sinf(angleRad);

		distX1 = distX1 * sinf(angleRad) - distY1 * cosf(angleRad);
		distX2 = distX2 * sinf(angleRad) - distY2 * cosf(angleRad);

		if (z1 > 0.f || z2 > 0.f) 
		{
			Vector2 i1 = Utils::intersectLines(distX1, z1, distX2, z2, -0.0001f, 0.0001f, -20, 5);
			Vector2 i2 = Utils::intersectLines(distX1, z1, distX2, z2, 0.0001f, 0.0001f, 20, 5);

			if (z1 <= 0) 
			{
				if (i1.y > 0) 
				{
					distX1 = i1.x;
					z1 = i1.y;
				}
				else 
				{
					distX1 = i2.x;
					z1 = i2.y;
				}
			}
			if (z2 <= 0) 
			{
				if (i1.y > 0)

				{

					distX2 = i1.x;

					z2 = i1.y;

				}

				else

				{

					distX2 = i2.x;

					z2 = i2.y;

				}
			}
		}
		else 
		{
			continue;
		}

		float widthRatio = W / 2.f;
		float heightRatio =	(W * H) / 60.f;

		float centerScreenW = W / 2.f;
		float centerScreenH = H / 2.f;

		float x1 = -distX1 * widthRatio / z1;
		float x2 = -distX2 * widthRatio / z2;
		float y1a = (ceilingHeight - heightRatio) / z1;
		float y1b = heightRatio / z1;
		float y2a = (ceilingHeight - heightRatio) / z2;
		float y2b = heightRatio / z2;

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		SDL_RenderLine(renderer, centerScreenW + x1, centerScreenH + y1a, centerScreenW + x2, centerScreenH + y2a);
		SDL_RenderLine(renderer, centerScreenW + x1, centerScreenH + y1b, centerScreenW + x2, centerScreenH + y2b);
		SDL_RenderLine(renderer, centerScreenW + x1, centerScreenH + y1a, centerScreenW + x1, centerScreenH + y1b);
		SDL_RenderLine(renderer, centerScreenW + x2, centerScreenH + y2a, centerScreenW + x2, centerScreenH + y2b);
	}
}
