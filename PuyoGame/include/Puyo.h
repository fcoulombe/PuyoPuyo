#ifndef PUYO_H
#define PUYO_H

#include <vector>

#include <Sprite.h>
namespace Game
{
	//this is the class that manages individual puyo which are the little balls in the game
	class Puyo
	{
	public:

		//the different states of a puyo
		enum PuyoState
		{
			PS_INACTIVE,
			PS_FALLING,
			PS_LANDED
		};

		//the different types of puyo
		enum PuyoType
		{
			PT_RED,
			PT_GREEN,
			PT_BLUE,
			PT_YELLOW,
			PT_PURPLE,
			PT_MAX
		};

		//constants
		static const size_t PUYO_WIDTH			= 32;
		static const size_t PUYO_HEIGHT			= 32;
		static const size_t PUYO_HALF_WIDTH		= PUYO_WIDTH/2;
		static const size_t PUYO_HALF_HEIGHT	= PUYO_HEIGHT/2;

		//functions
		Puyo(PuyoType type);

		void Update(const PuyoEngine::Vector2 &velocity);

		void Reset()
		{
			SetType(Puyo::PuyoType(rand()%Puyo::PT_MAX));
			SetState(PS_INACTIVE);
			SetVisible(false);
			mConnectedList.clear();
		}
		//connexions are puyo of the same color that touches
		void AddConnexion(Puyo *connexion) { mConnectedList.push_back(connexion); }

		void SetVisible(bool isVisible = true) { mSprite.SetVisible(isVisible); }
		void SetPosition(PuyoEngine::Real x, PuyoEngine::Real y) { mSprite.SetPosition(x,y); }
		void SetState(PuyoState state) {mCurrentState = state;}
		void SetType(PuyoType type);
		
		const PuyoEngine::Vector2 GetFieldPosition() const;
		const PuyoEngine::Vector2 &GetPosition() const { return mSprite.GetPosition(); }
		PuyoType GetType() const { return mType; }
		PuyoState GetState() const { return mCurrentState; }
		const std::vector<Puyo*> &GetConnexions() const { return mConnectedList; }
		
	private:
		//constants
		static const size_t PUYO_RED_FRAME		= 0;
		static const size_t PUYO_GREEN_FRAME	= 16;
		static const size_t PUYO_BLUE_FRAME		= 32;
		static const size_t PUYO_YELLOW_FRAME	= 48;
		static const size_t PUYO_PURPLE_FRAME	= 64;
		static const char *PUYO_TEXTURE;

		PuyoType mType;
		PuyoState mCurrentState;

		PuyoEngine::Sprite mSprite;
		std::vector<Puyo*> mConnectedList;
	};

	typedef std::vector<Puyo*> PuyoList;
}
#endif