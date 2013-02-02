#ifndef SHADERRESOURCEMANAGER_H
#define SHADERRESOURCEMANAGER_H
#include "PuyoAssert.h"
#include "ResourceManager.h"
namespace PuyoEngine
{
	//very simple resource manager for shaders
	class ShaderResourceManager : public ResourceManager
	{
	public:
		static void Initialize()
		{	
			PASSERT(smpInstance == NULL);
			smpInstance = new ShaderResourceManager();
		}
		static void Terminate()
		{
			PASSERT(smpInstance != NULL);
			delete smpInstance;
			smpInstance = NULL;
		}
		static ShaderResourceManager &Instance() {	PASSERT(smpInstance != NULL);return *smpInstance;}

		Resource *Allocate(const char *filename);
		void Free(Resource * /*resource*/);

	private:
		static ShaderResourceManager *smpInstance; 


		ShaderResourceManager() {}
	};
}

#endif