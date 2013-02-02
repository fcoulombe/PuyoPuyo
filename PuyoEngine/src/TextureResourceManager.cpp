#include "TextureResourceManager.h"


#include "PuyoAssert.h"
#include "TextureResource.h"



using namespace PuyoEngine;

TextureResourceManager *PuyoEngine::TextureResourceManager::smpInstance = NULL;

Resource * PuyoEngine::TextureResourceManager::Allocate( const char *filename )
{
	return new TextureResource(filename);
}

void PuyoEngine::TextureResourceManager::Free( Resource * /*resource*/ )
{

}