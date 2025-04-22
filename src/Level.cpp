#include "Level.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <SDL.h>
#include <queue>

//GLM stuff
#include "../libraries/glm/vec2.hpp"
#include "../libraries/glm/vec3.hpp"
#include "../libraries/glm/mat4x4.hpp"
#include "../libraries/glm/trigonometric.hpp"

#include "../libraries/glm/ext/matrix_transform.hpp"
#include "../libraries/glm/ext/matrix_clip_space.hpp"

//My stuff
#include "Utils.h"
#include "Camera.h"

void Level::addSectorToQueue(Sector* sec)
{
	sectorQueue.push(sec);
}

void Level::sortWallsAtSectorNum(unsigned sectorNum, Vector2 cameraPos)
{
	Sector* sec = &sectors.at(sectorNum);

	//This is doing a bubblesort, but right now the number of walls in a sector is so small it shouldn't matter that much

	for (unsigned i = 0; i < sec->getNumWalls() - 1; ++i) 
	{
		for (unsigned j = 0; j < sec->getNumWalls() - i - 1; ++j) 
		{
			Line* line1 = &lines.at(sec->getWallIndices()->at(j));
			Line* line2 = &lines.at(sec->getWallIndices()->at(j + 1));

			//If distance between line 1 and camera pos is less than distance between line 2 and camera pos
			if (fabsf(Utils::distance(Utils::midpt(line1->getStart(), line1->getEnd()), cameraPos)) < 
				fabsf(Utils::distance(Utils::midpt(line2->getStart(), line2->getEnd()), cameraPos)))
			{
				sec->swapWallIndexPositions(j, j + 1);
			}
		}
	}
}

/*
* A stub consisting of a lot of pseudo-code
* Call in updatePlayerSector to get which sector the player is in
* Starting sector is the last sector the player was in
*/
uint32_t Level::camInSector(Camera* cam)
{
	//Implement a ray-segment intersection test
	const Vector2 infLeft{ -2000000000.f, cam->getPosition().y };

	Sector* sec = &sectors.at(cam->getSectorNum());
	uint32_t secnum = sec->getID();

	unsigned count = 0;

	for (uint32_t i = 0; i < sec->getNumWalls(); ++i) 
	{
		Line* line = &lines.at(sec->getWallIndices()->at(i));

		//check line intersection
		//if intersection is true increment count

		//if count is odd you are in the sector, if not, you are outside
	}

	//if odd
	if ((count & 1) == 1) 
	{
		//Return current sector num
		return secnum;
	}
	else 
	{
		//check adjacent sectors
	}

	return 0;
}

Level::Level()
{

}

Level::~Level()
{

}

void Level::setDrawBounds(SDL_Surface* surface)
{
	//If size has not changed
	if ((lowerPixDrawn.size() == upperPixDrawn.size()) && lowerPixDrawn.size() == surface->w) 
	{
		for (uint16_t i = 0; i < surface->w; ++i) 
		{
			lowerPixDrawn.at(i) = surface->h - 1;
			upperPixDrawn.at(i) = 0;
		}
	}
	else //If size has changed
	{
		if (!lowerPixDrawn.empty() || !upperPixDrawn.empty())
		{
			lowerPixDrawn.clear();
			upperPixDrawn.clear();
		}

		for (uint16_t i = 0; i < surface->w; ++i)
		{
			lowerPixDrawn.push_back(surface->h - 1);
			upperPixDrawn.push_back(0);
		}
	}
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
			else if (fileline == "player") 
			{
				state = READ_PLAYER;
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
		else if (state == READ_PLAYER) 
		{
			//Set player position
			//Stub, add later
			getline(file, fileline);
		}
		file.peek();
	}

	file.close();

	//Debugging
	//for (unsigned i = 0; i < sectors.size(); ++i) 
	//{
	//	for (unsigned j = 0; j < sectors.at(i).getWallIndices()->size(); ++j) 
	//	{
	//		std::cout << "x1: " << lines.at(j).getStart().x << " y1: " << lines.at(j).getStart().y
	//			<< " x2: " << lines.at(j).getEnd().x << " y2: " << lines.at(j).getEnd().y << "\n\n";
	//	}
	//}

	//Testing
	addSectorToQueue(&sectors.at(0));

	return 0; //Success
}

void Level::updatePlayerSector(Camera* cam)
{
	sectorQueue.push(&sectors.at(cam->getSectorNum()));
	for (unsigned i = 0; i < drawnSectors.size(); ++i) 
	{
		drawnSectors.at(i) = false;
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

void Level::renderMap(SDL_Renderer* renderer, SDL_Surface* surf, Camera* cam)
{
	for (unsigned i = 0; i < lines.size(); ++i) 
	{
		lines.at(i).render2d(renderer, lines.at(i).getColor());
	}
}

void Level::render(SDL_Renderer* renderer, SDL_Surface* surface, Camera* cam)
{
	Sector* sec = &sectors.at(cam->getSectorNum());
	for (unsigned i = 0; i < sec->getNumWalls(); ++i) 
	{
		Line* lin = &lines.at(sec->getWallIndices()->at(i));

		//Don't render portals as walls
		if (lin->getPortalNum() != 0) 
		{
			continue;
		}

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

		float widthRatio = surface->w / 2.f;
		float heightRatio =	(surface->w * surface->h) / 60.f;

		float centerScreenW = surface->w / 2.f;
		float centerScreenH = surface->h / 2.f;

		float x1 = -distX1 * widthRatio / z1;
		float x2 = -distX2 * widthRatio / z2;
		float y1a = (ceilingHeight - heightRatio) / z1;
		float y1b = heightRatio / z1;
		float y2a = (ceilingHeight - heightRatio) / z2;
		float y2b = heightRatio / z2;

		SDL_Vertex verts[4];
		verts[0].position.x = centerScreenW + x1;
		verts[0].position.y = centerScreenH + y1a;
		verts[0].color = SDL_FColor{ 1.f, 0.f, 0.f, 1.f };

		verts[1].position.x = centerScreenW + x2;
		verts[1].position.y = centerScreenH + y2a;
		verts[1].color = SDL_FColor{ 1.f, 0.f, 0.f, 1.f };

		verts[2].position.x = centerScreenW + x1;
		verts[2].position.y = centerScreenH + y1b;
		verts[2].color = SDL_FColor{ 1.f, 0.f, 0.f, 1.f };

		verts[3].position.x = centerScreenW + x2;
		verts[3].position.y = centerScreenH + y2b;
		verts[3].color = SDL_FColor{ 1.f, 0.f, 0.f, 1.f };

		int indices[6] = { 0,1,2,2,3,1 };

		SDL_RenderGeometry(renderer, NULL, verts, 4, indices, 6);

		//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		//SDL_RenderLine(renderer, centerScreenW + x1, centerScreenH + y1a, centerScreenW + x2, centerScreenH + y2a); //Top
		//SDL_RenderLine(renderer, centerScreenW + x1, centerScreenH + y1b, centerScreenW + x2, centerScreenH + y2b); //Bottom
		//SDL_RenderLine(renderer, centerScreenW + x1, centerScreenH + y1a, centerScreenW + x1, centerScreenH + y1b);
		//SDL_RenderLine(renderer, centerScreenW + x2, centerScreenH + y2a, centerScreenW + x2, centerScreenH + y2b);
	}
}

void Level::renderSectors(SDL_Renderer* renderer, SDL_Surface* surface, Camera* cam)
{
	unsigned halfWidth = surface->w / 2;
	unsigned halfHeight = surface->h / 2;

	float fov = -(cam->getFov());

	//This might be how to handle perspective correction but I'm also not sure that I'm giving the correct values for width and height
	glm::mat4 persp = glm::perspectiveFov(cam->getFovRad(), surface->w - 1.f, surface->h - 1.f, 0.1f, 200.f);

	//Loop through all sectors in queue
	unsigned numSectors = sectorQueue.size();

	for (unsigned i = 0; i < numSectors; ++i)
	{
		Sector* sec = sectorQueue.front();

		sortWallsAtSectorNum(sec->getID() - 1, cam->getPosition());

		float fheight = sec->getFloorHeight();
		float cheight = sec->getCeilingHeight();

		drawnSectors.at(sec->getID() - 1) = true;

		//Loop through all lines in the sector
		for (unsigned j = 0; j < sec->getNumWalls(); ++j) 
		{
			Line* ln = &lines.at(sec->getWallIndices()->at(j));

			//Convert world coords
			float dx1 = ln->getStart().x - cam->getPosition().x;
			float dy1 = ln->getStart().y - cam->getPosition().y;
			float dx2 = ln->getEnd().x - cam->getPosition().x;
			float dy2 = ln->getEnd().y - cam->getPosition().y;

			float angleSin = sinf(Utils::degToRad(cam->getAngle()));
			float angleCos = cosf(Utils::degToRad(cam->getAngle()));

			//Rotate world
			float rx1 = dx1 * angleSin - dy1 * angleCos;
			float rz1 = dx1 * angleCos + dy1 * angleSin;
			float rx2 = dx2 * angleSin - dy2 * angleCos;
			float rz2 = dx2 * angleCos + dy2 * angleSin;

			//Clipping
			if (rz1 < 0 && rz2 < 0) 
			{
				continue;
			}
			if (rz1 < 0) 
			{
				Utils::clipBehindCamera(&rx1, &rz1, rx2, rz2);
			}
			else if (rz2 < 0) 
			{
				Utils::clipBehindCamera(&rx2, &rz2, rx1, rz1);
			}

			//Use later for drawing above and below portals
			float portBH1 = 0;
			float portBH2 = 0;
			float portTH1 = 0;
			float portTH2 = 0;

			//if is portal
			if (ln->getPortalNum() != 0)
			{
				//calculate
				if (!drawnSectors.at(ln->getPortalNum() - 1))
				{
					//This is messing up and causing flickering
					sectorQueue.push(&sectors.at(ln->getPortalNum() - 1));
					++numSectors;
				}
				continue;
			}

			//Get line height
			float height1 = -(cheight / rz1) * fov;
			float height2 = -(cheight / rz2) * fov;

			//Convert to screen space
			float sx1 = ((rx1 / rz1) * fov) - (surface->w / 2);
			float sy1 = ((surface->h + cam->getHeight()) / rz1);
			float sx2 = ((rx2 / rz2) * fov) - (surface->w / 2);
			float sy2 = ((surface->h + cam->getHeight()) / rz2);

			//Elevation from floor
			float secLev1 = ((fheight + cam->getHeight()) / rz1) * fov;
			float secLev2 = ((fheight + cam->getHeight()) / rz2) * fov;
			sy1 -= secLev1;
			sy2 -= secLev2;

			sx1 += halfWidth;
			sy1 += halfHeight;
			sx2 += halfWidth;
			sy2 += halfHeight;

			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			
			renderWall(renderer, surface, sx1, sx2, sy1 - height1, sy1, sy2 - height2, sy2, ln->getFcolor());
		}

		//Mark drawn sectors and dequeue
		//drawnSectors.at(sec->getID() - 1) = true;
		sectorQueue.pop();
	}
}

void Level::renderWall(SDL_Renderer* renderer, SDL_Surface* surface, float x1, float x2, float y1a, float y1b, float y2a, float y2b, SDL_FColor color)
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	
#define RENDER_TYPE 1

	//Testing
	//SDL_RenderLine(renderer, sx1, sy1 - height1, sx2, sy2 - height2); //Top
	//SDL_RenderLine(renderer, sx1, sy1, sx2, sy2); //Bottom
	//SDL_RenderLine(renderer, sx1, sy1 - height1, sx1, sy1);
	//SDL_RenderLine(renderer, sx2, sy2 - height2, sx2, sy2);

#if RENDER_TYPE == 0
	float topSlope = (Utils::calcLineSlope(x1, y1a, x2, y2a));
	float bottomSlope = (Utils::calcLineSlope(x1, y1b, x2, y2b));
	float ts = 0;
	float bs = 0;

	//Draw columns
	for (int16_t c = (int16_t)x1; c < (int16_t)x2; ++c)
	{
		//Check top bounds and bottom bounds in occlusion mask and clip accordingly
		float top = ((y2a - y1a) * ((c - x1) / (x2 - x1))) + y1a;
		float bottom = ((y2b - y1b) * ((c - x1) / (x2 - x1))) + y1b;
		Utils::drawVertLineColors(surface, SDL_clamp(c + (surface->w / 2), 0, surface->w - 1),
			                               SDL_clamp(y1a + ts, top, bottom),
			                               SDL_clamp(y1b + bs, top, bottom),
			                               0xffff0000, 0xff00ff00, 0xff0000ff);

		ts += topSlope;
		bs += bottomSlope;

		//upperPixDrawn.at(c);
		//lowerPixDrawn.at(c);
	}

#elif RENDER_TYPE == 1

	SDL_Vertex verts[4];
	verts[0].position.x = x1;
	verts[0].position.y = y1a;
	verts[0].color = color;

	verts[1].position.x = x2;
	verts[1].position.y = y2a;
	verts[1].color = color;

	verts[2].position.x = x1;
	verts[2].position.y = y1b;
	verts[2].color = color;

	verts[3].position.x = x2;
	verts[3].position.y = y2b;
	verts[3].color = color;

	int indices[6] = { 0,1,2,2,3,1 };

	SDL_RenderGeometry(renderer, NULL, verts, 4, indices, 6);
#endif
}
