#ifndef RENDERER_H
#define RENDERER_H
#include <vector>

#include "PuyoEngineTypes.h"
#include "Sprite.h"
#include "Vector2.h"

//this is the main renderer. it manages the sprite rendering and the states of opengl
namespace PuyoEngine
{
	class Sprite;
	typedef std::vector<const Sprite *> SpriteList;

	//our default vertex format
	struct VertexPT
	{
		VertexPT(const Vector2 &position,const Vector2 &uv )
			: mPosition(position), mTextureCoord(uv){}
		Vector2 mPosition;
		Vector2 mTextureCoord;
	};
	typedef VertexPT Vertex;
	typedef std::vector<Vertex> VertexList;

	class Renderer
	{
	public:
		static bool Initialize(size_t width, size_t height, size_t bpp);
		static void Terminate();

		static void PreRender();
		static void Render();
		static void PostRender();

		static void RegisterSprite(const Sprite *newSprite, SpriteLayers layer)	{mSpriteList[layer].push_back(newSprite);}
		static void UnRegisterSprite(const Sprite *sprite);

		static size_t GetScreenWidth() { return mWidth; }
		static size_t GetScreenHeight() { return mHeight; }

	private:
		static const size_t DEFAULT_WIDTH	= 640;
		static const size_t DEFAULT_HEIGHT	= 480;
		static const size_t DEFAULT_BPP		= 32;

		static size_t	mWidth, 
						mHeight, 
						mBpp;

		//sprite list for different sprite layer
		static SpriteList mSpriteList[SL_MAX];
	};
}

#endif