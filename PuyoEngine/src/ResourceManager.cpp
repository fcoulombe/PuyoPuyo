#include "ResourceManager.h"
#include "djbHash.h"
#include "PuyoAssert.h"
#include "Resource.h"

using namespace PuyoEngine;



const Resource * PuyoEngine::ResourceManager::LoadResource( const char *textureName )
{
	//hash the name for faster search in the tree
	uint32_t fileNameHash = DJBHash(textureName, strlen(textureName));

	//check if we have the resource in our ResourceManager
	ResourceCache::iterator it = mResourceCache.find(fileNameHash);
	if (it != mResourceCache.end())
	{	
		++it->second->mRefCount;
		return it->second;
	}

	//if we don't then load the resource
	Resource *newResource = Allocate(textureName);
	mResourceCache[fileNameHash] = newResource;
	return newResource;
}

//reduce the ref count
void PuyoEngine::ResourceManager::ReleaseResource( const Resource *resource )
{
	for (ResourceCache::iterator it = mResourceCache.begin(); it != mResourceCache.end(); ++it)
	{
		if (it->second == resource)
		{
			--it->second->mRefCount;
			PASSERT(resource->mRefCount>=0); //if we get a ref count of -1, something went really wrong;
			return;
		}
	}
	PASSERT_MSG(false, "we released a texture that didnt exist.");
}

