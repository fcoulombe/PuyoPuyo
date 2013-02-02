#include "ShaderResourceManager.h"

#include "ShaderResource.h"
using namespace PuyoEngine;

ShaderResourceManager *PuyoEngine::ShaderResourceManager::smpInstance = NULL;
Resource * PuyoEngine::ShaderResourceManager::Allocate( const char *filename )
{
	return new ShaderResource(filename);
}

void PuyoEngine::ShaderResourceManager::Free( Resource * /*resource*/ )
{

}