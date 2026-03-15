#ifndef _OpenGLAvailability_H
#define _OpenGLAvailability_H

#include <Availability.h>

#ifdef GL_SILENCE_DEPRECATION
	#define OPENGL_AVAILABLE(from)
	#define OPENGL_DEPRECATED(from, to)
	#define OPENGL_DEPRECATED_MSG(from, to, msg)
#else
	#define OPENGL_AVAILABLE(from) __API_AVAILABLE(macos(from))
	#define OPENGL_DEPRECATED(from, to) __API_DEPRECATED("OpenGL API deprecated. (Define GL_SILENCE_DEPRECATION to silence these warnings)", macos(from, to))
	#define OPENGL_DEPRECATED_MSG(from, to, msg) __API_DEPRECATED("" #msg "", macos(from, to))
#endif

#define OPENGL_ENUM_AVAILABLE(from) OPENGL_AVAILABLE(from)
#define OPENGL_ENUM_DEPRECATED(from, to) OPENGL_DEPRECATED(from, to)
#define OPENGL_ENUM_DEPRECATED_MSG(from, to, msg) OPENGL_DEPRECATED_MSG(from, to, msg)

#endif
