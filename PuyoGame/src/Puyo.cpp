#include "Puyo.h"

using namespace PuyoEngine;
using namespace Game;

const char *Puyo::PUYO_TEXTURE = "data/Texture/puyo.tga";

Puyo::Puyo(PuyoType type)
:	mSprite(PUYO_TEXTURE, PUYO_WIDTH,PUYO_HEIGHT),
	mCurrentState(PS_INACTIVE)
{
	SetType(type);
	mSprite.LoadShader("data/Shader/DefaultShader");
}


void Puyo::Update(const PuyoEngine::Vector2 &velocity)
{
	switch (mCurrentState)
	{
	case PS_INACTIVE:
		{
			mSprite.SetVisible(false);
			break;
		}
	case PS_FALLING:
		{
			mSprite.SetVisible(true);
			const Vector2 &position = mSprite.GetPosition();
			Vector2 newPosition(position.x+velocity.x, position.y+velocity.y);
			mSprite.SetPosition(newPosition);
			break;
		}
	case PS_LANDED:
		{
			//y correction

			break;
		}
	}
}

void Game::Puyo::SetType( PuyoType type )
{
	mType = type;
	switch (mType)
	{
	case PT_RED:
		mSprite.SetFrame(PUYO_RED_FRAME);
		break;
	case PT_GREEN:
		mSprite.SetFrame(PUYO_GREEN_FRAME);
		break;
	case PT_BLUE:
		mSprite.SetFrame(PUYO_BLUE_FRAME);
		break;
	case PT_YELLOW:
		mSprite.SetFrame(PUYO_YELLOW_FRAME);
		break;
	case PT_PURPLE:
		mSprite.SetFrame(PUYO_PURPLE_FRAME);
		break;
	default:
		PASSERT(false); //unknown puyo
	}
}

//just a test function to try to get the position in cell units
const Vector2 Game::Puyo::GetFieldPosition() const
{
	const Vector2 &position = mSprite.GetPosition();
	Vector2 fieldPosition(640.0f/2.0f, 480.0f/2.0f);
	Vector2 fieldSize(192.0f, 384.0f);
	Vector2 topleft(fieldPosition.x-(fieldSize.x/2.0f), fieldPosition.y-(fieldSize.y/2.0f));
	Vector2 delta = position - topleft;
	delta /= 32.0f;
	delta -= 0.5f;
	return delta;
}
