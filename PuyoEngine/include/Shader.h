#ifndef SHADER_H
#define SHADER_H

#include "ShaderResource.h"
#include "ShaderResourceManager.h"
#include "Vector2.h"

namespace PuyoEngine
{

	class Shader
	{
	public:
		Shader(const char *shaderName)
		{
			mResource = static_cast<const ShaderResource *>(ShaderResourceManager::Instance().LoadResource(shaderName));
		}
		~Shader()
		{
			ShaderResourceManager::Instance().ReleaseResource(mResource);
		}

		template<typename T> inline void SetUniform(const char *uniformName, T val);

	private:
		const ShaderResource *mResource;

	};


	template<> inline void Shader::SetUniform(const char *uniformName, const PuyoEngine::Vector2 &val)
	{
		glUseProgramObjectARB(mResource->mProgram);
		int location = glGetUniformLocationARB(mResource->mProgram, uniformName);
		glUniform2fARB(location, val.x, val.y);
	}
	template<> inline void Shader::SetUniform(const char *uniformName, const float val)
	{
		glUseProgramObjectARB(mResource->mProgram);
		int location = glGetUniformLocationARB(mResource->mProgram, uniformName);
		glUniform1fARB(location, val);
	}
	template<> inline void Shader::SetUniform(const char *uniformName, const int val)
	{
		glUseProgramObjectARB(mResource->mProgram);
		int location = glGetUniformLocationARB(mResource->mProgram, uniformName);
		glUniform1iARB(location, val);
	}


}

#endif