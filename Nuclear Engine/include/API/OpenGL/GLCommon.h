#include <NE_Common.h>

#ifdef NE_COMPILE_CORE_OPENGL
#include <GLAD\include\glad\glad.h>
//
//namespace NuclearEngine
//{
//	namespace API
//	{
//		namespace OpenGL
//		{
//			GLenum glCheckError_(const char *file, int line)
//			{
//				GLenum errorCode;
//				while ((errorCode = glGetError()) != GL_NO_ERROR)
//				{
//					std::string error;
//					switch (errorCode)
//					{
//					case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
//					case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
//					case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
//					case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
//					case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
//					case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
//					case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
//					}
//					Log.Error("[OpenGL Err] File: " + std::string(file) + " Line: " + std::to_string(line) + " Error: " + error);
//				}
//				return errorCode;
//			}
//#define glCheckError() glCheckError_(__FILE__, __LINE__)
//		}
//	}
//}
#endif
