#ifndef IGAMESTATE_H
#define IGAMESTATE_H

namespace Game
{
	//base game state for the other game states
	class IGameState
	{
	public:
		
		virtual void BeginGameState() = 0;
		virtual void Update() = 0;
		virtual void EndGameState() {delete this;}
	protected:
		virtual ~IGameState() {}

	};

	//an empty game state in case that we don't have a game state currently running
	//this allows us to run the update without performing an if statement on every frame 
	//just to know whether we are cuurnetly running a game state
	class EmptyGameState : public IGameState
	{
	public:
		/*virtual*/ void BeginGameState()	{}

		/*virtual*/void Update() {}

		/*virtual*/void EndGameState(){}

		static EmptyGameState Instance;
	};
}

#endif