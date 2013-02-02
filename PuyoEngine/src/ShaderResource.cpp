#include "ShaderResource.h"

#include <fstream>
#include <iostream>
#include <string>

#include "PuyoAssert.h"


using namespace PuyoEngine;


PuyoEngine::ShaderResource::ShaderResource( const char *filename)
{
	std::string vertexFilename(filename);;
	vertexFilename += std::string(".vs");
	std::fstream vfp(vertexFilename.c_str(), std::ios::in|std::ios::binary);
	PASSERT(vfp.is_open() && vfp.good());
	long begin_pos = vfp.tellg();
	vfp.seekg(0, std::ios_base::end);
	long filesize = vfp.tellg()-begin_pos;
	vfp.seekg(0, std::ios::beg);
	vfp.clear();
	char *vertexFile = new char[filesize+1];
	vfp.read(vertexFile, filesize);
	vertexFile[filesize] = '\0';
	vfp.close();

	std::string pixelFilename(filename);;
	pixelFilename = pixelFilename + std::string(".ps");
	std::fstream pfp(pixelFilename.c_str(), std::ios::in|std::ios::binary);
	PASSERT(pfp.is_open() && pfp.good());
	begin_pos = pfp.tellg();
	pfp.seekg(0, std::ios_base::end);
	filesize = pfp.tellg()-begin_pos;
	pfp.seekg(0, std::ios::beg);
	pfp.clear();
	char *pixelFile = new char[filesize+1];
	pfp.read(pixelFile, filesize);
	pixelFile[filesize] = '\0';
	pfp.close();

	mProgram		= glCreateProgramObjectARB();						glErrorCheck();
	
	mVertexShader	= glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);	glErrorCheck();
	glShaderSourceARB(mVertexShader, 1, (const GLcharARB **)&vertexFile, NULL);	glErrorCheck();
	glCompileShaderARB(mVertexShader);									glErrorCheck();
	PrintLog(mVertexShader);

	mFragmentShader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);	glErrorCheck();
	glShaderSourceARB(mFragmentShader, 1, (const GLcharARB **)&pixelFile, NULL);glErrorCheck();
	glCompileShaderARB(mFragmentShader);								glErrorCheck();
	PrintLog(mFragmentShader);

	// Attach The Shader Objects To The Program Object
	glAttachObjectARB(mProgram, mVertexShader);							glErrorCheck();
	glAttachObjectARB(mProgram, mFragmentShader);						glErrorCheck();

	// Link The Program Object
	glLinkProgramARB(mProgram);											glErrorCheck();

	// Use The Program Object Instead Of Fixed Function OpenGL
	glUseProgramObjectARB(mProgram);									glErrorCheck();


	delete [] vertexFile;
}

PuyoEngine::ShaderResource::~ShaderResource()
{
	glDeleteObjectARB(mProgram);
}

void PuyoEngine::ShaderResource::PrintLog(GLuint obj)
{
	int infologLength = 0;
	char infoLog[1024];

	if (glIsShader(obj))
		glGetShaderInfoLog(obj, 1024, &infologLength, infoLog);
	else
		glGetProgramInfoLog(obj, 1024, &infologLength, infoLog);

	if (infologLength > 0)
		std::cout << infoLog << std::endl;;


}