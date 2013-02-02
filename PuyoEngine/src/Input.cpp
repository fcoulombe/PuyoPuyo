#include "Input.h"


using namespace PuyoEngine;

//check what key has been pressed and store the result in a bool array
void PuyoEngine::Input::Update()
{
	memset(mKeyDown, 0, sizeof(mKeyDown));
	memset(mKeyUp, 0, sizeof(mKeyUp));
	//While there are events to handle
	while( SDL_PollEvent( &event ) )
	{
		//Handle key presses
		if( event.type == SDL_QUIT )
		{
			//mIsRunning = false;
		}
		else if( event.type == SDL_KEYDOWN )
		{
			//Adjust the velocity
			switch( event.key.keysym.sym )
			{
			case SDLK_UP: mKeyDown[K_UP] = true; break;
			case SDLK_DOWN: mKeyDown[K_DOWN] = true; break;
			case SDLK_LEFT: mKeyDown[K_LEFT] = true; break;
			case SDLK_RIGHT: mKeyDown[K_RIGHT] = true; break;
			case SDLK_RETURN: mKeyDown[K_ENTER] = true; break;
			}
		}
		//If a key was released
		else if( event.type == SDL_KEYUP )
		{
			//Adjust the velocity
			switch( event.key.keysym.sym )
			{
			case SDLK_UP: mKeyUp[K_UP] = true;  break;
			case SDLK_DOWN: mKeyUp[K_DOWN] = true; break;
			case SDLK_LEFT: mKeyUp[K_LEFT] = true; break;
			case SDLK_RIGHT: mKeyUp[K_RIGHT] = true; break;
			case SDLK_RETURN: mKeyUp[K_ENTER] = true; break;
			}
		}
	}
}