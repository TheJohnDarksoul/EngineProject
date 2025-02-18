#include <iostream>
#include <SDL.h>

#include "GameWindow.h"
#include "datastructs.h"
#include "levelcomponents.h"
#include "Utils.h"

#include "Camera.h"

#define FOREWARD_PRESSED 0b1
#define FOREWARD_RELEASED FOREWARD_PRESSED ^ UINT_MAX
#define BACKWARD_PRESSED 0b10
#define BACKWARD_RELEASED BACKWARD_PRESSED ^ UINT_MAX
#define LEFT_PRESSED 0b100
#define LEFT_RELEASED LEFT_PRESSED ^ UINT_MAX
#define RIGHT_PRESSED 0b1000
#define RIGHT_RELEASED RIGHT_PRESSED ^ UINT_MAX
#define USE_PRESSED 0b10000
#define USE_RELEASED USE_PRESSED ^ UINT_MAX

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
	if (SDL_Init(SDL_INIT_VIDEO) == false) 
	{
		//std::cout << "Video failed to init!\n";
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Init Failure", "SDL video failed to init", NULL);
		return 1;
	}

	Camera testCam;
	testCam.setPosition(100.f, 100.f);

	InputMap inputMap;

	inputMap.p_foreward = SDLK_W;
	inputMap.p_backward = SDLK_S;
	inputMap.p_left = SDLK_A;
	inputMap.p_right = SDLK_D;
	inputMap.p_use = SDLK_E;

	unsigned int pressedActions = 0;

	GameWindow window{640, 360};

	bool isOpen = true;

	SDL_HideCursor();

	while (isOpen) 
	{
		SDL_Event e;

		while (SDL_PollEvent(&e)) 
		{
			if (e.type == SDL_EVENT_QUIT) 
			{
				isOpen = false;
			}
			else if (e.type == SDL_EVENT_KEY_DOWN) 
			{
				//Test code
				//Can't use a switch on a non-const value
				if (e.key.key == inputMap.p_foreward) 
				{
					//std::cout << "Foreward pressed!\n";
					pressedActions |= FOREWARD_PRESSED;
					//std::cout << pressedActions << "\n";
				}
				else if (e.key.key == inputMap.p_backward) 
				{
					//std::cout << "Backward pressed!\n";
					pressedActions |= BACKWARD_PRESSED;
					//std::cout << pressedActions << "\n";
				}
				else if (e.key.key == inputMap.p_left) 
				{
					//std::cout << "Left pressed!\n";
					pressedActions |= LEFT_PRESSED;
					//std::cout << pressedActions << "\n";
				}
				else if (e.key.key == inputMap.p_right) 
				{
					//std::cout << "Right pressed!\n";
					pressedActions |= RIGHT_PRESSED;
					//std::cout << pressedActions << "\n";
				}
				else if (e.key.key == inputMap.p_use) 
				{
					//std::cout << "Use pressed!\n";
					pressedActions |= USE_PRESSED;
					//std::cout << pressedActions << "\n";
				}
			}
			else if (e.type == SDL_EVENT_KEY_UP) 
			{
				//Also test code
				if (e.key.key == inputMap.p_foreward)
				{
					//std::cout << "Foreward released!\n";
					pressedActions &= FOREWARD_RELEASED;
					//std::cout << pressedActions << "\n";
				}
				else if (e.key.key == inputMap.p_backward) 
				{
					//std::cout << "Backward released!\n";
					pressedActions &= BACKWARD_RELEASED;
					//std::cout << pressedActions << "\n";
				}
				else if (e.key.key == inputMap.p_left) 
				{
					//std::cout << "Left released!\n";
					pressedActions &= LEFT_RELEASED;
					//std::cout << pressedActions << "\n";
				}
				else if (e.key.key == inputMap.p_right)
				{
					//std::cout << "Right released!\n";
					pressedActions &= RIGHT_RELEASED;
					//std::cout << pressedActions << "\n";
				}
				else if (e.key.key == inputMap.p_use) 
				{
					//std::cout << "Use released!\n";
					pressedActions &= USE_RELEASED;
					//std::cout << pressedActions << "\n";
				}
			}
		}

		//Do updates
		//Test code
		if ((pressedActions & RIGHT_PRESSED) == RIGHT_PRESSED) 
		{
			testCam.rotate(0.1f);
			//std::cout << "rotate right\n";
		}
		if ((pressedActions & LEFT_PRESSED) == LEFT_PRESSED) 
		{
			testCam.rotate(-0.1f);
			//std::cout << "rotate left\n";
		}

		if ((pressedActions & FOREWARD_PRESSED) == FOREWARD_PRESSED) 
		{
			testCam.move(0.1 * cosf(Utils::degToRad(testCam.getAngle())), 0.1 * sinf(Utils::degToRad(testCam.getAngle())), 0, 1);
		}
		if ((pressedActions & BACKWARD_PRESSED) == BACKWARD_PRESSED)
		{
			testCam.move(-0.1 * cosf(Utils::degToRad(testCam.getAngle())), -0.1 * sinf(Utils::degToRad(testCam.getAngle())), 0, 1);
		}

		//Start of rendering frame
		window.clearRenderer();

		//test floor
		for (int y = 360 / 2; y < 360; ++y) 
		{
			int col = y / 2;
			SDL_SetRenderDrawColor(window.getRenderer(), col, col, col, 255);
			SDL_RenderLine(window.getRenderer(), 0, y, 640, y);
		}

		SDL_SetRenderDrawColor(window.getRenderer(), 0xb2, 0xb2, 0xff, 0xff);

		for (unsigned char i = 0; i < 19; ++i) 
		{
			testSegments[i].render2d(window.getRenderer());
		}

		testCam.render2d(window.getRenderer());

		//End of rendering frame
		window.presentRenderer();
	}

	SDL_Quit();

	return 0;
}