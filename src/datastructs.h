#pragma once

typedef struct
{
	float x;
	float y;
}Vector2;

//Holds the keycodes for in-game actions to allow rebinding
typedef struct 
{
	uint32_t p_foreward;
	uint32_t p_left;
	uint32_t p_right;
	uint32_t p_backward;
	uint32_t p_use;
	uint32_t p_rotateleft;
	uint32_t p_rotateright;
	uint32_t p_toggleMap;
	uint8_t p_lmb;
	uint8_t p_rmb;
}InputMap;

//Maybe add transformation matricies here