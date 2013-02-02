
#include <ctime>
#include <Input.h>
#include <PuyoOpenGL.h>
#include <Renderer.h>

#include "PuyoGame.h"

#include "IGameState.h"
#include "IntroGameState.h"
#include "PlayGameState.h"

using namespace PuyoEngine;
using namespace Game;

PuyoGame *PuyoGame::mspInstance = NULL;

//The timer
Timer::Timer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }

    //If the timer isn't running
    return 0;
}

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
}

Game::PuyoGame::PuyoGame()
: mIsRunning(true),
mCurrentGameState(&EmptyGameState::Instance)
{
	srand((unsigned int)time(NULL));

	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		throw;
	}

	if( !Renderer::Initialize(SCREEN_WIDTH,SCREEN_HEIGHT, SCREEN_BPP) )
	{
		throw;
	}

	SDL_WM_SetCaption( "Puyo-Puyo", NULL );

	mCurrentGameState->BeginGameState();
	SetGameState(new IntroGameState());
}

Game::PuyoGame::~PuyoGame()
{
	mCurrentGameState->EndGameState();
	Renderer::Terminate();
    SDL_Quit();
}

void Game::PuyoGame::Update()
{
	Input::Instance().Update();
	mCurrentGameState->Update();
}

void Game::PuyoGame::Render()
{
	Renderer::PreRender();
	Renderer::Render();
	Renderer::PostRender();
}

void Game::PuyoGame::SetGameState(IGameState *newGameState)
{
	mCurrentGameState->EndGameState();
	mCurrentGameState = newGameState;
	newGameState->BeginGameState();
}