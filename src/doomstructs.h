#pragma once

#include <cstdint>
#include <iostream>

//Here for reference, check the coder space video and translate that into c++

//Vertex
typedef struct 
{
	float x;
	float y;
}Vert;

//Line
typedef struct 
{
	uint32_t start;
	uint32_t end;

	uint8_t flags;
	bool interactable;
	std::string script;

	uint32_t frontSide;
	uint32_t backSide;
	
}Line;

//Side
typedef struct 
{
	int32_t xOffset;
	int32_t yOffset;

	std::string upperTexture;
	std::string middleTexture;
	std::string lowerTexture;

	uint32_t sectorNum;
}Side;

//Sector
typedef struct
{
	float floorHeight;
	float ceilingHeight;

	uint8_t lightLevel;

	std::string floorTexture;
	std::string ceilingTexture;

	std::string sectorScript;

	uint32_t sectorTag;
}Sector;