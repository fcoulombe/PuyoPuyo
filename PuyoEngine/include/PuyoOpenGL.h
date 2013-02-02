#ifndef PUYO_OPENGL_H
#define PUYO_OPENGL_H

//generic header to include opengl (its usually good if you want to disable completly opengl)
#include <SDL.h>
//#define GL_GLEXT_PROTOTYPES

#include "GL/glew.h"
//#include <SDL_opengl.h>

//#define GLEW_MX

/*

extern PFNGLUSEPROGRAMPROC					glUseProgramObjectARB;
extern PFNGLLINKPROGRAMARBPROC				glLinkProgramARB;
extern PFNGLATTACHOBJECTARBPROC				glAttachObjectARB;
extern PFNGLCREATEPROGRAMOBJECTARBPROC		glCreateProgramObjectARB;
extern PFNGLCREATESHADEROBJECTARBPROC		glCreateShaderObjectARB;
extern PFNGLSHADERSOURCEARBPROC				glShaderSourceARB;
extern PFNGLCOMPILESHADERARBPROC			glCompileShaderARB;
extern PFNGLDELETEOBJECTARBPROC				glDeleteObjectARB;
extern PFNGLISSHADERPROC					glIsShader;
extern PFNGLGETSHADERINFOLOGPROC			glGetShaderInfoLog;
extern PFNGLGETPROGRAMINFOLOGPROC			glGetProgramInfoLog;
extern PFNGLUNIFORM1FARBPROC				glUniform1fARB;*/

//glerror macro that can be called after gl functions in debug
#if defined (PUYO_CONFIG_DEBUG)
void iGLErrorCheck()
{
	GLenum err = glGetError();
	if( err != GL_NO_ERROR )
	{
		const char *errorString;
		switch (err)
		{
		case GL_NO_ERROR:
			{
				errorString = "	No error has been recorded.The value of this symbolic constant is guaranteed to be 0.";
				break;
			}
		case GL_INVALID_ENUM:
			{
				errorString = "An unacceptable value is specified for an enumerated argument.The offending command is ignored and has no other side effect than to set the error flag.";
				break;
			}
		case GL_INVALID_VALUE:
			{
				errorString = "	A numeric argument is out of range.	The offending command is ignored and has no other side effect than to set the error flag.";
				break;
			}
		case GL_INVALID_OPERATION:
			{
				errorString = "The specified operation is not allowed in the current state.	The offending command is ignored and has no other side effect than to set the error flag";
				break;
			}
		case GL_STACK_OVERFLOW:
			{
				errorString = "This command would cause a stack overflow.The offending command is ignored	and has no other side effect than to set the error flag.";
				break;
			}
		case GL_STACK_UNDERFLOW:
			{
				errorString = "This command would cause a stack underflow.The offending command is ignored	and has no other side effect than to set the error flag.";
				break;
			}
		case GL_OUT_OF_MEMORY:
			{
				errorString = "There is not enough memory left to execute the command.The state of the GL is undefined,	except for the state of the error flags,after this error is recorded.";
				break;
			}
		case GL_TABLE_TOO_LARGE:
			{
				errorString = "The specified table exceeds the implementation's maximum supported table	size.  The offending command is ignored and has no other side effect than to set the error flag.";
				break;
			}
		default:
			{
				errorString " unknown error";
			}
		}
		PASSERT_MSG(false, errorString);
	}
}

#define glErrorCheck() do { iGLErrorCheck() } while(false);
#else
inline void NoOp() {}
#define glErrorCheck() do { NoOp(); } while(false);
#endif


#endif