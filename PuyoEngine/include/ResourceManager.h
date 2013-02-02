#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>

#include "PuyoEngineTypes.h"
namespace PuyoEngine
{

	class Resource;
	class ResourceManager
	{
	public:
		const Resource *LoadResource(const char *textureName) ;
		void ReleaseResource(const Resource *resource) ;

		virtual Resource *Allocate(const char *filename)=0;
		virtual void Free(Resource *resource)=0;
	protected:
		typedef std::map<uint32_t, Resource*> ResourceCache;
		ResourceCache mResourceCache;

	};

}

#endif