#ifndef INTROGAMESTATE_H
#define INTROGAMESTATE_H

#include "IGameState.h"
#include <Input.h>
#include <Sprite.h>

#include "PlayGameState.h"
namespace Game
{

	//this is just the intro game state that displays the logo and how to play information
	class IntroGameState : public IGameState
	{
	public:
		IntroGameState() 
			: mLogo("data/Texture/logo.tga", 569,304){}
		/*virtual*/ void BeginGameState()
		{
			mLogo.SetPosition(640.0f/2.0f, 480.0f/2.0f);
			mLogo.SetVisible();

			mLogo.LoadShader("data/Shader/DefaultShader");

		}

		/*virtual*/void Update()
		{

			mLogo.Update();
			if (PuyoEngine::Input::Instance().IsKeyDown(PuyoEngine::Input::K_ENTER))
			{
				PuyoGame::Instance().SetGameState(new PlayGameState());
			}
		}

		/*virtual*/void EndGameState()
		{

			Inherit::EndGameState();

		}
		typedef IGameState Inherit;


		PuyoEngine::Sprite mLogo;
	};

}

#endif