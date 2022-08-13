#pragma once

#include <glad/glad.h>


namespace dvr::gl::debug {

#if defined(_DEBUG)

	void GLAPIENTRY message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* user_param); 

	inline void callback() {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(message_callback, nullptr);
	}
#else
	inline void callback() {}
#endif

}