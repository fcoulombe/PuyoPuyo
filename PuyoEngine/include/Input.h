#ifndef INPUT_H
#define INPUT_H
#include <SDL.h>
namespace PuyoEngine
{

	//class to manage the inputs
	class Input
	{
	public:

		enum Keys
		{
			K_UP,
			K_DOWN,
			K_LEFT,
			K_RIGHT,
			K_SPACE,
			K_ENTER,
			K_MAX
		};

		static Input &Instance() 
		{
			static Input instance;
			return instance;
		}
		void Update();

		bool IsKeyDown(Keys key) const { return mKeyDown[key]; }

	private:
		Input() {}

		bool mKeyDown[K_MAX];
		bool mKeyUp[K_MAX];
		SDL_Event event;

	};

}
#endif