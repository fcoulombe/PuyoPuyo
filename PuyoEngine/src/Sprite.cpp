#include "Sprite.h"

#include "Renderer.h"
using namespace PuyoEngine;


PuyoEngine::Sprite::Sprite( const char *textureName, size_t frameWidth, size_t frameHeight, SpriteLayers layer ) 
: mTexture(textureName),
mFrameWidth(frameWidth),
mFrameHeight(frameHeight),
mCurrentFrame(0),
mIsVisible(false),
mIsLooping(true),
mIsPlaying(false),
mPosition(0.0f, 0.0f),
mMinUV(0.0f,0.0f),
mMaxUV(1.0f,1.0f),
mScale(1.0f,1.0f),
mRotation(0.0f)
{
	mpShader		= NULL;
	size_t width	= mTexture.GetWidth();
	size_t height	= mTexture.GetHeight();
	mMaxFrame		= (width/mFrameWidth) * (height/mFrameHeight);

	CalculateUV();
	Renderer::RegisterSprite(this, layer);
}

void PuyoEngine::Sprite::LoadShader(const char *shaderFileName)
{
	mpShader = new Shader(shaderFileName);

	mpShader->SetUniform("texture1", 0);
}

PuyoEngine::Sprite::~Sprite()
{
	Renderer::UnRegisterSprite(this);
}

//update the animation if we're currently playing one
void PuyoEngine::Sprite::Update()
{
	if (mIsPlaying)
	{
		++mCurrentFrame;
		if (mCurrentFrame == mMaxFrame)
		{
			if (mIsLooping)
				mCurrentFrame = 0;
			else
				--mCurrentFrame;
		}
		CalculateUV();
	}
}

//this function calculates the current UV coordinate based ont he current frame
void Sprite::CalculateUV()
{
	size_t textureWidth  = mTexture.GetWidth();
	size_t textureHeight = mTexture.GetHeight();

	size_t row		= ((mCurrentFrame)*mFrameWidth) / textureWidth;
	size_t column	= mCurrentFrame-((textureWidth/mFrameWidth)*row);

	Real u		= Real(column*mFrameWidth)/Real(textureWidth);
	Real v		= 1.0f - Real(row*mFrameHeight)/Real(textureHeight);
	mMinUV.x	= u;
	mMinUV.y	= v;
	u			= Real((column+1)*mFrameWidth)/Real(textureWidth);
	v			= 1.0f - Real((row+1)*mFrameHeight)/Real(textureHeight);
	mMaxUV.x	=  u;
	mMaxUV.y	=  v;
}
