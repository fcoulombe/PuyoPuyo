
#include "PlayGameState.h"

#include <algorithm> 
#include <iostream>

#include <Input.h>
#include <Renderer.h>

using namespace Game;
using namespace PuyoEngine;

//constant definition
const Real Game::PlayGameState::START_Y_POSITION(64.0f);
const Real Game::PlayGameState::DEFAULT_GRAVITY(1.0f);


const char *Game::PlayGameState::FIELD_TEXTURE			= "data/Texture/field.tga";
const char *Game::PlayGameState::FIELD_BORDER_TEXTURE	= "data/Texture/fieldborder.tga";
const char *Game::PlayGameState::WAITING_BOX_TEXTURE	= "data/Texture/waitingbox_layout.tga";
const char *Game::PlayGameState::GAME_OVER_TEXTURE		= "data/Texture/game_over.tga";


Game::PlayGameState::PlayGameState() 
: mCurrentGravity(1.0f),
mField(FIELD_TEXTURE, FIELD_WIDTH,FIELD_HEIGHT, SL_BACKGROUND),
mFieldBorder(FIELD_BORDER_TEXTURE, 220,400, SL_BACKGROUND),
mWaitingBoxLayout(WAITING_BOX_TEXTURE , 72,48, SL_BACKGROUND),
mGameOver(GAME_OVER_TEXTURE, 512,256, SL_OVERLAY)
{
	mGameOver.SetPosition(Real(Renderer::GetScreenWidth())/2.0f, Real(Renderer::GetScreenHeight())/2.0f);
	mField.SetPosition(Real(Renderer::GetScreenWidth())/2.0f, Real(Renderer::GetScreenHeight())/2.0f);
	mFieldBorder.SetPosition(Real(Renderer::GetScreenWidth())/2.0f, Real(Renderer::GetScreenHeight())/2.0f);
	mWaitingBoxLayout.SetPosition(Real(WAITING_LIST_POSITION_X-16), Real(WAITING_LIST_POSITION_X));
	
	mFieldBorder.SetVisible();
	mField.SetVisible();
	mWaitingBoxLayout.SetVisible();
}

void Game::PlayGameState::BeginGameState()
{
	//create all the puyos and start up the game. we keep them in an innactive list until we need them
	const size_t fieldSize = FIELD_CELL_WIDTH*FIELD_CELL_HEIGHT;
	mLandedPuyoList.reserve(fieldSize);
	mInactivePuyoList.reserve(fieldSize);
	for (size_t i=0; i<fieldSize; ++i)
	{
		mInactivePuyoList.push_back(new Puyo(Puyo::PT_RED));
		
	}
	mCurrentState = FS_DROP_NEW_PUYO;
	AddNewBlockToWaitingList();
	SetInputEnabled(true);
	mLineCount = 0;
}

void Game::PlayGameState::Reset()
{
	mGameOver.SetVisible(false);
	for (size_t i=0; i<mWaitingList.size(); i++)
	{
		mWaitingList[i]->Reset();
		mInactivePuyoList.push_back(mWaitingList[i]);
	}
	mWaitingList.clear();
	for (size_t i=0; i<mFallingPuyo.size(); i++)
	{
		mFallingPuyo[i]->Reset();
		mInactivePuyoList.push_back(mFallingPuyo[i]);
	}
	mFallingPuyo.clear();
	for (size_t i=0; i<mLandedPuyoList.size(); i++)
	{
		mLandedPuyoList[i]->Reset();
		mInactivePuyoList.push_back(mLandedPuyoList[i]);
	}
	mLandedPuyoList.clear();
	mIsInputEnabled = true;
	mCurrentGravity = DEFAULT_GRAVITY;
	mLineCount = 0;
	mCurrentState = FS_DROP_NEW_PUYO;

}

void Game::PlayGameState::Update()
{
	switch (mCurrentState)
	{
		//state for when our field is full
	case FS_BUSTED:
		{
			mGameOver.SetVisible();

			//whenever we press enter, we reset the game
			if (Input::Instance().IsKeyDown(Input::K_ENTER))
			{
				Reset();
				AddNewBlockToWaitingList();
			}

		break;
		}
		//in this state, we grab the puyo in the waiting area and we drop them in the field
		//we check right away if they collide with anything which would mean that we are BUSTED
	case FS_DROP_NEW_PUYO:
		{
			mCurrentState = FS_FALLING;
			Puyo *tempPuyo = mWaitingList[0];
			tempPuyo->SetPosition((Real(Renderer::GetScreenWidth())/2.0f)+Puyo::PUYO_HALF_WIDTH, START_Y_POSITION);
			tempPuyo->SetState(Puyo::PS_FALLING);
			if (IsCollidePointCollideWithLandedBlocks(tempPuyo->GetPosition()))
			{
				mCurrentState = FS_BUSTED;
			}
			mFallingPuyo.push_back(tempPuyo);
			
			tempPuyo = mWaitingList[1];
			tempPuyo->SetPosition((Real(Renderer::GetScreenWidth())/2.0f)-Puyo::PUYO_HALF_WIDTH, START_Y_POSITION);
			tempPuyo->SetState(Puyo::PS_FALLING);
			mFallingPuyo.push_back(tempPuyo);
			if (IsCollidePointCollideWithLandedBlocks(tempPuyo->GetPosition()))
			{
				mCurrentState = FS_BUSTED;
			}
			mWaitingList.clear();
			AddNewBlockToWaitingList();
			
			break;
		}
		//this is the state where the puyo are falling. most of the heavy logic happens here
	case FS_FALLING:
		{
			//detect velocity based on input
			Vector2 velocity(0.0f, mCurrentGravity+((mLineCount/10)+1));

			//detect the input
			bool rotateCCW = false;
			if (mIsInputEnabled)
			{
				//If a key was pressed
				if (Input::Instance().IsKeyDown(Input::K_UP))
					rotateCCW = true; 
				else if (Input::Instance().IsKeyDown(Input::K_DOWN))
					velocity.y += 1.0f; 
				else if (Input::Instance().IsKeyDown(Input::K_LEFT))
					velocity.x -= Puyo::PUYO_WIDTH; 
				else if (Input::Instance().IsKeyDown(Input::K_RIGHT))
					velocity.x+= Puyo::PUYO_WIDTH; 
			}

			//perform rotation
			if (rotateCCW && mFallingPuyo.size()>1)
			{
				Vector2 delta	= mFallingPuyo[1]->GetPosition() -mFallingPuyo[0]->GetPosition();
				Real	radian	= Math::DegreeToRadian(90.0f);
				Vector2 newDelta;
				newDelta.x = (delta.x*cos(radian)) + (delta.y*sin(radian));
				newDelta.y = (delta.x*-sin(radian)) + (delta.y*cos(radian));

				Vector2 finalPosition = mFallingPuyo[0]->GetPosition() +newDelta;
				if (!IsCollidePointCollideWithSideWall(finalPosition) && !IsCollidePointCollideWithLandedBlocks(finalPosition))
					mFallingPuyo[1]->SetPosition(finalPosition.x, finalPosition.y);
			}


			//if we're moving side ways, check if we collide with anything
			if (velocity.x != 0.0f && (IsCollideWithWalls(velocity) || IsCollideWithOtherBlocks(velocity)))
			{	
				//cancel movement
				velocity.x = 0.0f;
			}	

			//this is the complicated section. since we have 2 blocks that are falling, it is possible to update the first one
			//then the second lands but the first one should have collided with the second one. so we need to run the routine 
			//as many time as we have blocks that land in the current frame
			PuyoList howManyBlockHasLanded;
			bool hasAnyBlockLanded = false;
			do 
			{
				howManyBlockHasLanded.clear();
				for (size_t i=0; i<mFallingPuyo.size(); ++i)
				{
					Puyo *tempPuyo = mFallingPuyo[i];	
					if (!CheckCollisionAgainstLandedBlocks(tempPuyo, velocity, mLandedPuyoList, howManyBlockHasLanded))
						continue;

					//create the connexions
					//basically if we have landed, we establish connexion between the current block
					//and any other block of the same color
					//this will be used later on to know if we have 4 or more blocks touching
					for (size_t z=0; z<mLandedPuyoList.size(); ++z)
					{
						Puyo *tempPuyo2 = mLandedPuyoList[z];
						if (tempPuyo2->GetType() != tempPuyo->GetType())
							continue;
						const Vector2 delta = tempPuyo2->GetPosition()-tempPuyo->GetPosition();
						if (delta.GetSquaredLength() <= (Puyo::PUYO_WIDTH+1)*(Puyo::PUYO_WIDTH+1))
						{
							tempPuyo->AddConnexion(tempPuyo2);
							tempPuyo2->AddConnexion(tempPuyo);
						}
					}

					//update the puyo's position one last time
					tempPuyo->Update(velocity);

					//	put in landed puyo list since its no longer falling
					mLandedPuyoList.push_back(tempPuyo);
					mFallingPuyo[i] = mFallingPuyo[mFallingPuyo.size()-1];
					mFallingPuyo.pop_back();
					hasAnyBlockLanded = true;
					break;
				}
			}while (howManyBlockHasLanded.size());

			//update the falling puyo's position
			for (size_t i=0; i<mFallingPuyo.size(); ++i)
			{
				mFallingPuyo[i]->Update(velocity);
			}

			//if every puyo has landed, check if there are any 4 in a row connexion
			if (!mFallingPuyo.size())
			{
				bool hasAnyBlockBeenNuked = false;
				for (size_t i=0; i<mLandedPuyoList.size(); ++i)
				{
					//check if we have a serie
					Puyo *tempPuyo = mLandedPuyoList[i];
					connected.clear();
					FillConnectedArray(connected, tempPuyo); //recursive function that figures out a list of connexion of the same color
					//if we have 4 or more connexions
					if (connected.size()>=NUM_PUYO_CONNECTED_FOR_A_LINE) 
					{
						//mCurrentState = FS_DESTROY_CONNECTED;
						hasAnyBlockBeenNuked = true;
						//destroy the blocks and send them back to inactive list
						for (size_t z=0; z<connected.size(); ++z)
						{
							Puyo *tempConnexion = connected[z];
							PuyoList::iterator it = std::find(mLandedPuyoList.begin(), mLandedPuyoList.end(), tempConnexion);
							PASSERT(it != mLandedPuyoList.end());
							mLandedPuyoList.erase(it);
							mInactivePuyoList.push_back(tempConnexion);
							tempConnexion->SetState(Puyo::PS_INACTIVE);
							tempConnexion->SetVisible(false);
						}
						++mLineCount;
						i =0; //need to restart since we dont know where the blocks got deleted from

					}
				}
				//since puyo's have been destroyed, we set all the other blocks into a falling state since they might have holes under them
				if (hasAnyBlockBeenNuked)
				{
					SetInputEnabled(false);

					for (size_t i=0; i<mLandedPuyoList.size(); ++i)
					{
						mLandedPuyoList[i]->SetState(Puyo::PS_FALLING);
						mFallingPuyo.push_back(mLandedPuyoList[i]);
					}
					mLandedPuyoList.clear();
				}
				else
				{
					//time to drop new puyo in our field
					SetInputEnabled(true);
					mCurrentState = FS_DROP_NEW_PUYO;
				}
			}

			break;
		}
		//this is a state to perform whatever visual effect to destroy the pouyo
	case FS_DESTROY_CONNECTED:
		{

			break;
		}
	}
}


//routine that grabs 2 puyos from the innactive list, reset them and add them to the waiting list
void Game::PlayGameState::AddNewBlockToWaitingList()
{
	Puyo *tempPuyo = mInactivePuyoList[mInactivePuyoList.size()-1];
	tempPuyo->Reset();
	mWaitingList.push_back(tempPuyo);
	mInactivePuyoList.pop_back();
	tempPuyo->SetPosition(PuyoEngine::Real(WAITING_LIST_POSITION_X), PuyoEngine::Real(WAITING_LIST_POSITION_Y));
	tempPuyo->SetVisible();

	tempPuyo = mInactivePuyoList[mInactivePuyoList.size()-1];
	tempPuyo->Reset();
	mWaitingList.push_back(tempPuyo);
	mInactivePuyoList.pop_back();
	tempPuyo->SetPosition(PuyoEngine::Real(WAITING_LIST_POSITION_X-Puyo::PUYO_WIDTH), PuyoEngine::Real(WAITING_LIST_POSITION_Y));
	tempPuyo->SetVisible();

}

//collision detection function

bool Game::PlayGameState::IsCollideWithWalls(PuyoEngine::Vector2 &velocity) const
{
	for (size_t i=0; i<mFallingPuyo.size(); ++i)
	{
		Puyo *tempPuyo = mFallingPuyo[i];	
		const Vector2 &position = tempPuyo->GetPosition();

		Vector2 newPosition(position.x+velocity.x, position.y+velocity.y);

		if (IsCollidePointCollideWithSideWall(newPosition))
		{
			velocity.x = 0.0f;
			return true;
		}
		if (IsCollidePointCollideWithFloor(newPosition))
		{
			velocity.y = 0.0f;
		}

	}

	return false;
}
bool Game::PlayGameState::IsCollideWithOtherBlocks(const Vector2 &velocity) const
{
	for (size_t i=0; i<mFallingPuyo.size(); ++i)
	{
		Puyo *tempPuyo = mFallingPuyo[i];	
		const Vector2 &position = tempPuyo->GetPosition();

		Vector2 newPosition(position.x+velocity.x, position.y);

		for (size_t j=0; j<mLandedPuyoList.size(); ++j)
		{
			Vector2 delta = mLandedPuyoList[j]->GetPosition()-newPosition;
			if (delta.GetSquaredLength() < 32*32)
			{
				return true;
			}
		}
	}
	return false;

}

//creates a list of all the connexions
bool Game::PlayGameState::FillConnectedArray(PuyoList &connected,Puyo *puyo)
{
	//check if puyo already in list
	for (size_t i=0; i<connected.size(); ++i)
	{
		if (connected[i] == puyo)
			return false;
	}

	//add it and check its connexion
	connected.push_back(puyo);
	const std::vector<Puyo*> &connexionList = puyo->GetConnexions();
	for (size_t i=0; i<connexionList.size(); ++i)
	{
		FillConnectedArray(connected, connexionList[i]);
	}

	return true;

}
bool Game::PlayGameState::IsCollidePointCollideWithLandedBlocks(const Vector2 &position) const
{
	for (size_t j=0; j<mLandedPuyoList.size(); ++j)
	{
		Vector2 delta = mLandedPuyoList[j]->GetPosition()-position;
		if (delta.GetSquaredLength() < Puyo::PUYO_WIDTH*Puyo::PUYO_WIDTH)
			return true;
	}
	return false;
}

bool Game::PlayGameState::CheckCollisionAgainstLandedBlocks(Puyo *tempPuyo, const Vector2 &velocity,const PuyoList &activePuyos, PuyoList &justLandedPuyo)
{
	const Vector2 &position = tempPuyo->GetPosition();
	Vector2 newPosition(position.x+velocity.x, position.y+velocity.y);
	//test collision with other puyos
	for (size_t j=0; j<activePuyos.size(); ++j)
	{
		const Vector2 &lhs = activePuyos[j]->GetPosition();
		Vector2 delta = lhs-newPosition;
		if (delta.GetSquaredLength() < Puyo::PUYO_WIDTH*Puyo::PUYO_WIDTH)
		{
			tempPuyo->SetPosition(lhs.x, lhs.y-Puyo::PUYO_WIDTH);
			tempPuyo->SetState(Puyo::PS_LANDED);
			justLandedPuyo.push_back(tempPuyo);
			return true;
		}
	}

	//if we touch the floor
	if (newPosition.y >= FIELD_FLOOR-Puyo::PUYO_HALF_HEIGHT)
	{
		tempPuyo->SetState(Puyo::PS_LANDED);
		justLandedPuyo.push_back(tempPuyo);
		return true;
	}
	return false;
}

//end of the game. clean up the resources
void Game::PlayGameState::EndGameState()
{
	for (size_t i=0; i<mWaitingList.size(); i++)
	{
		delete mWaitingList[i];
	}
	mWaitingList.clear();
	for (size_t i=0; i<mFallingPuyo.size(); i++)
	{	
		delete mFallingPuyo[i];
	}
	mFallingPuyo.clear();
	for (size_t i=0; i<mLandedPuyoList.size(); i++)
	{	
		delete mLandedPuyoList[i];
	}
	mLandedPuyoList.clear();
	for (size_t i=0; i<mInactivePuyoList.size(); i++)
	{	
		delete mInactivePuyoList[i];
	}
	mInactivePuyoList.clear();

	//destroy the field and all the puyos
	Inherit::EndGameState();
}