#pragma once

typedef struct
{
	float x;
	float y;
}Vector2;

//Holds the keycodes for in-game actions to allow rebinding
typedef struct 
{
	unsigned int p_foreward;
	unsigned int p_left;
	unsigned int p_right;
	unsigned int p_backward;
	unsigned int p_use;
}InputMap;