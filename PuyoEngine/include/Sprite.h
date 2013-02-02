#ifndef SPRITE_H
#define SPRITE_H
#include "Texture.h"
#include "Shader.h"
#include "Vector2.h"

namespace PuyoEngine
{
	//sprite layers from back to front
	enum SpriteLayers
	{
		SL_BACKGROUND,
		SL_SPRITES,
		SL_OVERLAY,
		SL_MAX
	};

	//sprite class
	class Sprite
	{
	public:
		//frame width and height is in case that we have a multi frame sprite, 
		//we tell it the size of one frame and the class figures out the rest
		Sprite(const char *textureName, size_t frameWidth, size_t frameHeight, SpriteLayers layer = SL_SPRITES);
		~Sprite();

		void LoadShader(const char *shaderFileName);

		void Update();

		void SetFrame(size_t frame) { mCurrentFrame = frame; CalculateUV(); }
		void Play()					{mIsPlaying = true;	}
		void Stop()					{ Pause(); mCurrentFrame = 0; }
		void Pause()				{ mIsPlaying = false; }

		bool IsAnimationFinish() const { return mCurrentFrame == mMaxFrame; }

		//bind the current texture
		void Bind() const {	glBindTexture(GL_TEXTURE_2D, mTexture.GetTextureHandle());glErrorCheck();}

		void SetPosition(const Vector2 &position)	{ mPosition = position; }
		void SetPosition(Real x, Real y)			{ mPosition.x = x; mPosition.y = y; }
		void SetVisible(bool isVisible=true)		{ mIsVisible = isVisible; }

		const Vector2 &GetMinUV() const			{ return mMinUV; }
		const Vector2 &GetMaxUV() const			{ return mMaxUV; }
		const Vector2 &GetPosition() const		{ return mPosition; }
		const Vector2 &GetScale() const			{ return mScale; }
		Real GetRotation() const				{ return mRotation; }
		size_t GetWidth() const					{ return mFrameWidth; }
		size_t GetHeight() const				{ return mFrameHeight; }
		bool IsVisible() const					{ return mIsVisible; }

	private:
		void CalculateUV();
		
		bool	mIsLooping;
		bool	mIsPlaying;
		bool	mIsVisible;

		Texture mTexture; //4 bytes
		Shader *mpShader;
		size_t	mFrameWidth, 
				mFrameHeight;
		size_t	mCurrentFrame;
		size_t	mMaxFrame;

		Real	mRotation;
		Vector2 mMinUV;
		Vector2 mMaxUV;
		Vector2 mPosition;
		Vector2 mScale;
	};

}

#endif