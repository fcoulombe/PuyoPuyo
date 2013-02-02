#ifndef TEXTURERESOURCE_H
#define TEXTURERESOURCE_H
#include "PuyoOpenGL.h"
#include "Resource.h"
namespace PuyoEngine
{
	//this is a resource class that can be shared between difference texture instance
	struct TextureResource : public Resource
	{
		TextureResource(const char *textureName);
		~TextureResource();
		

		GLuint mTextureHandle;
		GLenum mMinFilter;
		GLenum mMagFilter;
		GLenum mWrapModeS;
		GLenum mWrapModeT;
		GLenum mTextureFormat;
		GLuint  mBytePerPixel;
		GLuint mBpp;
		GLsizei mWidth, mHeight;
	};
}
#endif