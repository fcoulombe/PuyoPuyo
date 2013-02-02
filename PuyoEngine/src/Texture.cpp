#include "Texture.h"

#include "TextureResourceManager.h"
/*#include <SDL.h>
#include <SDL_video.h>
*/

using namespace PuyoEngine;

PuyoEngine::Texture::~Texture()
{
	TextureResourceManager::Instance().ReleaseResource(mTexResource);
}


PuyoEngine::Texture::Texture( const char *textureName )
{
	mTexResource = static_cast<const TextureResource*>(TextureResourceManager::Instance().LoadResource(textureName));
}