#include <iostream>
#include <SDL.h>
#include <cstdint>
#include <string>

#include "inputflags.h"

#include "GameWindow.h"
#include "datastructs.h"
#include "levelcomponents.h"
#include "Utils.h"

#include "Camera.h"

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) == false) 
	{
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

	//SDL_HideCursor();

	uint64_t currentTime = SDL_GetTicks();

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

		//Change to fixed timestep later
		uint64_t newTime = SDL_GetTicks();

		float delta = (newTime - currentTime) / 1000.f;

		currentTime = newTime;

		Vector2 camPos = testCam.getPosition();

		//Do updates
		//Test code
		if ((pressedActions & RIGHT_PRESSED) == RIGHT_PRESSED) 
		{
			testCam.rotate(90.f * delta);
			//std::cout << "rotate right\n";
		}
		if ((pressedActions & LEFT_PRESSED) == LEFT_PRESSED) 
		{
			testCam.rotate(-90.f * delta);
			//std::cout << "rotate left\n";
		}

		if ((pressedActions & FOREWARD_PRESSED) == FOREWARD_PRESSED) 
		{
			testCam.move(100 * cosf(Utils::degToRad(testCam.getAngle())), 100 * sinf(Utils::degToRad(testCam.getAngle())), 0, delta);
		}
		if ((pressedActions & BACKWARD_PRESSED) == BACKWARD_PRESSED)
		{
			testCam.move(-100 * cosf(Utils::degToRad(testCam.getAngle())), -100 * sinf(Utils::degToRad(testCam.getAngle())), 0, delta);
		}

		//Start of rendering frame
		window.clearRenderer();

		Utils::drawVertLineColor(SDL_GetWindowSurface(window.getWindow()), 100, 0, 200, 0xffffffff);

		//test floor, not very good and won't work with multiple floor heights but is here for demoing
		//for (int y = 360 / 2; y < 360; ++y) 
		//{
		//	int col = y / 2;
		//	SDL_SetRenderDrawColor(window.getRenderer(), col, col, col, 255);
		//	SDL_RenderLine(window.getRenderer(), 0, y, 640, y);
		//}

		testCam.render2d(window.getRenderer());

		SDL_SetRenderDrawColor(window.getRenderer(), 0xff, 0xff, 0xff, 0xff);

		std::string dText = "Position: " + std::to_string(testCam.getPosition().x) + ", " + std::to_string(testCam.getPosition().y) + " Angle: "
			+ std::to_string(testCam.getAngle());

		SDL_RenderDebugText(window.getRenderer(), 0, 359 - 8, dText.c_str());

		//End of rendering frame
		window.presentRenderer();
	}

	SDL_Quit();

	return 0;
}