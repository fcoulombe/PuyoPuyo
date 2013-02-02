#ifndef PLAYGAMESTATE_H
#define PLAYGAMESTATE_H
#include <vector> 

#include <PuyoEngineTypes.h>

#include "IGameState.h"
#include "Puyo.h"

namespace Game
{
	//this is the main game state
	//most of the game logic will be run withing this class
	class PlayGameState : public IGameState
	{
	public:
		PlayGameState();
		/*virtual*/ void BeginGameState();

		/*virtual*/void Update();

		/*virtual*/void EndGameState();
		

	private:
		typedef IGameState Inherit;

		//those are the sub states for this game state
		enum FieldState
		{
			FS_FALLING,
			FS_DESTROYING,
			FS_DROP_NEW_PUYO,
			FS_DESTROY_CONNECTED,
			FS_BUSTED
		};

		//
		// constants. they are static private variable to keep them within the scope of this class
		// i prefer those to void namespaces. justa  personal preference
		//
		static const size_t NUM_PUYO_CONNECTED_FOR_A_LINE = 4;
		static const size_t FIELD_WIDTH			= 192;
		static const size_t FIELD_HEIGHT		= 384;

		static const size_t FIELD_CELL_WIDTH	= 6;
		static const size_t FIELD_CELL_HEIGHT	= 12;
		static const size_t FIELD_WIDTH_OFFSET	= 640/2;
		static const size_t FIELD_HEIGHT_OFFSET	= 480/2;
		static const size_t FIELD_FLOOR			= 432;

		static const PuyoEngine::Real START_Y_POSITION;
		static const PuyoEngine::Real DEFAULT_GRAVITY;

		static const size_t WAITING_LIST_POSITION_X = 128;
		static const size_t WAITING_LIST_POSITION_Y = 128;

		static const char *FIELD_TEXTURE;
		static const char *FIELD_BORDER_TEXTURE;
		static const char *WAITING_BOX_TEXTURE;
		static const char *GAME_OVER_TEXTURE;

		static bool FillConnectedArray(PuyoList &connected,Puyo *puyo);

		//layout sprites
		PuyoEngine::Sprite mField;
		PuyoEngine::Sprite mFieldBorder;
		PuyoEngine::Sprite mWaitingBoxLayout;
		PuyoEngine::Sprite mGameOver;
		
		//puyo lists
		PuyoList mLandedPuyoList;
		PuyoList mFallingPuyo;
		PuyoList mWaitingList;
		PuyoList mInactivePuyoList;
		PuyoList connected;
		
		//game data
		bool				mIsInputEnabled;
		PuyoEngine::Real	mCurrentGravity;
		size_t				mLineCount;
		FieldState			mCurrentState;

		//falling blocks have landed, time to drop new blocks
		void AddNewBlockToWaitingList();
	
		//disable inputs
		void SetInputEnabled(bool isInputEnabled = true) { mIsInputEnabled = isInputEnabled; }

		void Reset();
		//utility functions
		bool IsCollideWithWalls(PuyoEngine::Vector2 &velocity) const;
		bool IsCollideWithOtherBlocks(const PuyoEngine::Vector2 &velocity) const;
		bool IsCollidePointCollideWithLandedBlocks(const PuyoEngine::Vector2 &position) const;
		bool IsCollidePointCollideWithSideWall(const PuyoEngine::Vector2 &point) const {return (point.x >= 416.0f) || (point.x <= 228.0f);}
		bool IsCollidePointCollideWithFloor(const PuyoEngine::Vector2 &point) const {return (point.y >= 432.0f-16.0f);}
		bool CheckCollisionAgainstLandedBlocks(Puyo *tempPuyo, const PuyoEngine::Vector2 &velocity,	const PuyoList &activePuyos, PuyoList &justLandedPuyo);

	};


}

#endif