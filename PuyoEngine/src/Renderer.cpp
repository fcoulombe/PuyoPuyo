#include "Renderer.h"

#include <iostream>

#include "PuyoOpenGL.h"
#include "Texture.h"
#include "TextureResourceManager.h"
using namespace PuyoEngine;

size_t		Renderer::mWidth(DEFAULT_WIDTH); 
size_t		Renderer::mHeight(DEFAULT_HEIGHT); 
size_t		Renderer::mBpp(DEFAULT_BPP);
SpriteList	Renderer::mSpriteList[SL_MAX];

static Texture *newText=NULL;

static Sprite *newsprite = NULL;

void DetectExtension()
{

	//PFNGLACTIVETEXTUREPROC glActiveTexture;
}

bool PuyoEngine::Renderer::Initialize( size_t width, size_t height, size_t bpp )
{
	DetectExtension();
	mWidth	= width;
	mHeight = height;
	mBpp	= bpp;
	//Create Window
	if( SDL_SetVideoMode( (int)width, (int)height, (int)bpp, SDL_OPENGL ) == NULL )
	{
		return false;
	}
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;	
	}
	const char *ext = (const char *)glGetString (GL_EXTENSIONS) ;
#if 0
	std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

	std::cout << "GL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GL Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	
	std::cout << "GL Extensions: " << ext << std::endl;
#endif
	if (strstr(ext, "ARB_texture_non_power_of_two") == NULL)
		std::cerr << "non power of 2 texture supported" << std::endl;

/*
	glUseProgramObjectARB		= (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgramObjectARB");
	glLinkProgramARB			= (PFNGLLINKPROGRAMARBPROC)wglGetProcAddress("glLinkProgramARB");
	glAttachObjectARB			= (PFNGLATTACHOBJECTARBPROC)wglGetProcAddress("glAttachObjectARB");
	glCreateProgramObjectARB	= (PFNGLCREATEPROGRAMOBJECTARBPROC)wglGetProcAddress("glCreateProgramObjectARB");
	glCreateShaderObjectARB		= (PFNGLCREATESHADEROBJECTARBPROC)wglGetProcAddress("glCreateShaderObjectARB");
	glShaderSourceARB			= (PFNGLSHADERSOURCEARBPROC)wglGetProcAddress("glShaderSourceARB");
	glCompileShaderARB			= (PFNGLCOMPILESHADERARBPROC)wglGetProcAddress("glCompileShaderARB");
	glDeleteObjectARB			= (PFNGLDELETEOBJECTARBPROC)wglGetProcAddress("glDeleteObjectARB");
	glIsShader					= (PFNGLISSHADERPROC)wglGetProcAddress("glIsShader");
	glGetShaderInfoLog			= (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
	glGetProgramInfoLog			= (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");

	glUniform1fARB				= (PFNGLUNIFORM1FARBPROC)wglGetProcAddress("glUniform1fARB");;
	glUniform2fARB				= (PFNGLUNIFORM1FARBPROC)wglGetProcAddress("glUniform2fARB");;
	glUniform1iARB				= (PFNGLUNIFORM1FARBPROC)wglGetProcAddress("glUniform1iARB");;*/
	

	//Set clear color. blue in debug for easier debugging
#ifdef PUYOENGINE_CONFIG_DEBUG
	glClearColor( 0, 0, 1, 0 );
#else
	glClearColor( 0, 0, 0, 0 );
#endif

	//Set projection
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	//setup orthographic projection
	glOrtho( 0, width, height, 0, -1, 1 );

	//Initialize texture matrix
	glMatrixMode( GL_TEXTURE );
	glLoadIdentity();

	//Initialize modelview matrix
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	TextureResourceManager::Initialize();
	ShaderResourceManager::Initialize();
	return true;

}

void PuyoEngine::Renderer::Terminate()
{

}

//initialize the different render states needed
void PuyoEngine::Renderer::PreRender()
{
	glClear(GL_COLOR_BUFFER_BIT) /*GL_DEPTH_BUFFER_BIT|*/; glErrorCheck();
	

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, mWidth, mHeight, 0, -1, 1 ); glErrorCheck();

	glMatrixMode( GL_TEXTURE);
	glLoadIdentity();

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glEnable(GL_BLEND);									glErrorCheck();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	glErrorCheck();
	
	glDisable(GL_ALPHA_TEST);							glErrorCheck();
	glAlphaFunc(GL_GREATER,0.1f);						glErrorCheck();
	glEnable(GL_TEXTURE_2D);							glErrorCheck();
	glDisable(GL_DEPTH_TEST);							glErrorCheck();
	glDisable(GL_LIGHTING);								glErrorCheck();
	glDisable(GL_STENCIL_TEST);							glErrorCheck();
	
}

//loop through the different layers and draw all the different sprites
void PuyoEngine::Renderer::Render()
{
	glColor4f(1.0f,1.0f,1.0f, 1.0f);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	for (size_t j=0; j<SL_MAX; ++j)
	{
		SpriteList &spriteList = mSpriteList[j];

		for (size_t i=0; i<spriteList.size(); ++i)
		{
			const Sprite *tempSprite = spriteList[i];
			if (!tempSprite->IsVisible())
				continue;
			const Vector2 &uv0		= tempSprite->GetMinUV();
			const Vector2 &uv1		= tempSprite->GetMaxUV();
			const Vector2 &position = tempSprite->GetPosition();
			const Vector2 &scale	= tempSprite->GetScale();
			Real rotation			= tempSprite->GetRotation();
			Real width				= Real(tempSprite->GetWidth())/2.0f;
			Real height				= Real(tempSprite->GetHeight())/2.0f;

			glPushMatrix();
			glScalef(scale.x, scale.y,1.0f);
			glRotatef(rotation, 0.0f, 0.0f, 1.0f);
			glTranslatef(position.x, position.y, 0.0f);

			tempSprite->Bind();

			Vertex vertices[] = { 
				Vertex(Vector2(-width, height), Vector2(uv0.x, uv1.y)),
				Vertex(Vector2(width, height), Vector2(uv1.x, uv1.y)),
				Vertex(Vector2(width, -height), Vector2(uv1.x, uv0.y)),
				Vertex(Vector2(-width, -height), Vector2(uv0.x, uv0.y)),
			};     
			GLubyte indices[] = {1,0,3,2,1};

			glVertexPointer(2, GL_FLOAT, sizeof(Vertex), vertices); glErrorCheck();
			glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (uint8_t*)(vertices)+sizeof(Vector2));glErrorCheck();
			glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_BYTE, indices);glErrorCheck();
			glPopMatrix();
		}
	}
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}


void PuyoEngine::Renderer::PostRender()
{
	SDL_GL_SwapBuffers();
}

//remove the sprite from our layers
void PuyoEngine::Renderer::UnRegisterSprite( const Sprite *sprite )
{
	for (size_t j=0; j<SL_MAX; ++j)
	{
		SpriteList &spriteList = mSpriteList[j];
		size_t spriteCount = spriteList.size();
		for (size_t i=0; i<spriteCount; ++i)
		{
			const Sprite *tempSprite = spriteList[i];
			if (tempSprite == sprite)
			{
				spriteList[i] = spriteList[spriteCount-1];
				spriteList.pop_back();
				return;
			}
		}
	}
}