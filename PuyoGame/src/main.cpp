
#include <iostream>

#include <PuyoOpenGL.h>
#include "PuyoGame.h"


using namespace Game;

static const size_t FRAMES_PER_SECOND	= 60;

int main( int /*argc*/, char ** /*argv */)
{
	try
	{
		PuyoGame::Initialize();
		PuyoGame &game = PuyoGame::Instance();

		//The frame rate regulator
		Timer fps;

		//Wait for user exit
		while( game.IsRunning() )
		{
			//Start the frame timer
			fps.start();

			game.Update();
			game.Render();

			//Cap the frame rate
			if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
			{
				SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
			}
		}
	}
	catch (...)
	{
		std::cerr << "an exception has been thrown (most probablu during initialization). we're bailing out" << std::endl;
	}

	PuyoGame::Terminate();
	return 0;
}
