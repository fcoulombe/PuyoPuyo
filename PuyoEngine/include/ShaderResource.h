#ifndef SHADERRESOURCE_H
#define SHADERRESOURCE_H

#include "PuyoOpenGL.h"
#include "Resource.h"
namespace PuyoEngine
{

	class ShaderResource : public Resource
	{
	public:
		ShaderResource(const char *filename);

		~ShaderResource();

		GLenum mProgram;
		GLenum mVertexShader;
		GLenum mFragmentShader;


	private:
		void PrintLog(GLuint obj);


	};


}
#endif