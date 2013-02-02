#include "TextureResource.h"


#include <fstream>
#include <iostream>

#include "PuyoAssert.h"
#include "TGALoaderData.h"
using namespace PuyoEngine;


//this loads TGA files and then upload it to opengl
PuyoEngine::TextureResource::TextureResource( const char *textureName ) 
: Resource(),
mMinFilter(GL_LINEAR),
mMagFilter(GL_LINEAR),
mWrapModeS(GL_CLAMP),
mWrapModeT(GL_CLAMP)
{
	std::fstream fp(textureName, std::fstream::binary|std::fstream::in);
	PASSERT(fp.is_open() && fp.good());

	TGAHeader header ;
	fp.seekg (0, std::ios::beg);
	fp.read((char*)&header, sizeof(TGAHeader));
	GLubyte *imageData;
	//check if header is uncompressed
	if(memcmp(TGAUncompressedHeader, &header, sizeof(TGAHeader)) == 0)
	{

		TGA tga;
		fp.read((char*)&tga.header, sizeof(tga.header));

		mWidth	= tga.width		= tga.header[1] * 256 + tga.header[0];
		mHeight = tga.height	= tga.header[3] * 256 + tga.header[2];
		mBpp	=  tga.bpp		= tga.header[4];

		//test that we have power rof 2 textture
		if ( (mWidth & (mWidth - 1))	!= 0  && 
			(mHeight & (mHeight - 1))	!= 0 ) 
		{
			std::cout << "Warning: " << textureName << "is not a power of 2" << std::endl;
		}
		if(mBpp == 24)		
			mTextureFormat	= GL_RGB;		
		else if (mBpp == 32)
			mTextureFormat	= GL_RGBA;		

		mBytePerPixel = tga.bytesPerPixel = mBpp/8;
		tga.imageSize = (tga.bytesPerPixel * tga.width * tga.height);
		imageData =  new GLubyte[tga.imageSize];

		fp.read((char*)imageData, tga.imageSize);

		//swap the R and the B
		for(GLuint cswap = 0; cswap < (int)tga.imageSize; cswap += tga.bytesPerPixel)
		{
			uint8_t temp = imageData[cswap];
			imageData[cswap] = imageData[cswap+2];
			imageData[cswap+2] = temp;
		}
	}
	//check if header is compressed
	else if(memcmp(TGACompressedHeader, &header, sizeof(TGAHeader)) == 0)
	{				
		imageData = NULL;
		PASSERT(false); //unsupported

	}
	//unknown header
	else			
	{
		imageData = NULL;
		PASSERT(false);
	}				

	fp.close();

	glGenTextures( 1, &mTextureHandle );
	glBindTexture(	 GL_TEXTURE_2D, mTextureHandle );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mMinFilter );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mMagFilter );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mWrapModeS );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mWrapModeT);
	glTexImage2D(	 GL_TEXTURE_2D, 0, mBytePerPixel, mWidth, mHeight, 0,mTextureFormat, GL_UNSIGNED_BYTE, imageData );

	delete [] imageData;
}

PuyoEngine::TextureResource::~TextureResource()
{
	glDeleteTextures(1, &mTextureHandle);
}

