#include <iostream>
#include <SDL.h>

#include "GameWindow.h"
#include "datastructs.h"
#include "levelcomponents.h"

Vector2 testPoints[] = { {10.0, 10.0}, {70.0, 10.0}, {70.0, 80.0}, {10.0, 80.0},
						 {50.0, 20.0}, {40.0, 40.0}, {50.0, 60.0}, {60.0, 40.0},
						 {18.0, 18.0}, {18.0, 42.0}, {35.0, 42.0}, {35.0, 18.0},
						 {15.0, 55.0}, {15.0, 65.0}, {20.0, 65.0}, {20.0, 55.0},
						 {32.5, 48.0}, {27.0, 71.0}, {38.0, 71.0} };

Segment testSegments[] = {{testPoints[4], testPoints[5]}, {testPoints[5], testPoints[6]}, {testPoints[6], testPoints[7]}, {testPoints[7], testPoints[4]},
						  {testPoints[0], testPoints[1]}, {testPoints[1], testPoints[2]}, {testPoints[2], testPoints[3]}, {testPoints[3], testPoints[0]},
						  {testPoints[8], testPoints[9]}, {testPoints[9], testPoints[10]}, {testPoints[10], testPoints[11]}, {testPoints[11], testPoints[8]},
						  {testPoints[12], testPoints[13]}, {testPoints[13], testPoints[14]}, {testPoints[14], testPoints[15]}, {testPoints[15], testPoints[12]},
						  {testPoints[16], testPoints[17]}, {testPoints[17], testPoints[18]}, {testPoints[18], testPoints[16]}};

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		std::cout << "Video failed to init!\n";
		return 1;
	}

	GameWindow window;

	bool isOpen = true;

	while (isOpen) 
	{
		SDL_Event e;

		while (SDL_PollEvent(&e)) 
		{
			if (e.type == SDL_EVENT_QUIT) 
			{
				isOpen = false;
			}
		}

		window.clearRenderer();

		SDL_SetRenderDrawColor(window.getRenderer(), 0xb2, 0xb2, 0xff, 0xff);

		for (unsigned char i = 0; i < 19; ++i) 
		{
			testSegments[i].render2d(window.getRenderer());
		}

		window.presentRenderer();
	}

	SDL_Quit();

	return 0;
}