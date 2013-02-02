#ifndef TEXTURERESOURCEMANAGER_H
#define TEXTURERESOURCEMANAGER_H


#include "PuyoAssert.h"

#include "ResourceManager.h"

namespace PuyoEngine
{
	//very simple resource manager for texture
	//when something asks it to load a texture, it will hash the name and then
	//look in the map if we already have this texture loaded. if its the case, it will return 
	//a reference and increase the ref count. this is so that we don't waste memory loading similar textures
	struct TextureResource;
	class TextureResourceManager : public ResourceManager
	{
	public:
		static void Initialize()
		{	
			PASSERT(smpInstance == NULL);
			smpInstance = new TextureResourceManager();
		}
		static void Terminate()
		{
			PASSERT(smpInstance != NULL);
			delete smpInstance;
			smpInstance = NULL;
		}
		static TextureResourceManager &Instance() {	PASSERT(smpInstance != NULL);return *smpInstance;}

		Resource *Allocate(const char *filename);
		void Free(Resource * /*resource*/);

	private:
		static TextureResourceManager *smpInstance; 

		
		TextureResourceManager() {}
	};

}

#endif
