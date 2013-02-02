#ifndef PUYOGAME_H
#define PUYOGAME_H
#include <PuyoAssert.h>

namespace Game
{

	class IGameState;
	class Timer
	{
	private:
		//The clock time when the timer started
		int startTicks;

		//The ticks stored when the timer was paused
		int pausedTicks;

		//The timer status
		bool paused;
		bool started;

	public:
		//Initializes variables
		Timer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		int get_ticks();

		//Checks the status of the timer
		bool is_started();
		bool is_paused();
	};

	class PuyoGame
	{
	public:

		static void Initialize()
		{
			PuyoEngine::PASSERT(mspInstance == NULL);
			mspInstance = new PuyoGame();
		}
		static void Terminate()
		{
			PuyoEngine::PASSERT(mspInstance!=NULL);
			delete mspInstance;
			mspInstance = NULL;
		}
		static PuyoGame &Instance()
		{
			PuyoEngine::PASSERT(mspInstance!=NULL);
			return *mspInstance;	
		}
		void Update();
		void Render();
		bool IsRunning() const { return mIsRunning; }

		void SetGameState(IGameState *newGameState);
	private:
		//static
		static const size_t SCREEN_WIDTH		= 640;
		static const size_t SCREEN_HEIGHT		= 480;
		static const size_t SCREEN_BPP			= 32;

		static PuyoGame *mspInstance;

		PuyoGame();
		~PuyoGame();

		IGameState *mCurrentGameState;
		
		//var
		bool mIsRunning;
		
	};

}

#endif