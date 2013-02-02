#ifndef TEXTURE_H
#define TEXTURE_H
#include "PuyoOpenGL.h"
#include "TextureResource.h"
namespace PuyoEngine
{
	//this is the texture handle class
	//right now it only manages the texture resource
	class Texture
	{
	public:
		Texture(const char *textureName);
		~Texture();

		size_t GetWidth() const { return (size_t)mTexResource->mWidth; }
		size_t GetHeight() const { return (size_t)mTexResource->mHeight; }

		GLuint GetTextureHandle() const { return mTexResource->mTextureHandle; }
	private:
		const TextureResource *mTexResource;



	};

	
}
#endif