#pragma once

#include <glad/glad.h>

#include <unordered_map>


namespace gl_debug {

#ifndef NDEBUG

	std::unordered_map<GLenum, const char*> debug_source{ {GL_DEBUG_SOURCE_API, "API"}, {GL_DEBUG_SOURCE_WINDOW_SYSTEM, "WindowSystem"}, {GL_DEBUG_SOURCE_SHADER_COMPILER, "ShaderCompiler"},
		{GL_DEBUG_SOURCE_THIRD_PARTY, "ThirdParty"}, {GL_DEBUG_SOURCE_APPLICATION, "Application"}, {GL_DEBUG_SOURCE_OTHER, "Other"} };

	std::unordered_map<GLenum, const char*> debug_type{ {GL_DEBUG_TYPE_ERROR, "Error"}, {GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR, "Deprecated"}, {GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR, "Undefined"},
		{GL_DEBUG_TYPE_PORTABILITY, "Portability"}, {GL_DEBUG_TYPE_PERFORMANCE, "Performance"}, {GL_DEBUG_TYPE_MARKER, "Marker"}, {GL_DEBUG_TYPE_PUSH_GROUP, "Push Group"},
		{GL_DEBUG_TYPE_POP_GROUP, "Pop Group"}, {GL_DEBUG_TYPE_OTHER, "Other"} };

	std::unordered_map<GLenum, const char*> debug_severity{ {GL_DEBUG_SEVERITY_HIGH, "High"}, {GL_DEBUG_SEVERITY_MEDIUM, "Medium"}, 
												{GL_DEBUG_SEVERITY_LOW, "Low"}, {GL_DEBUG_SEVERITY_NOTIFICATION, "Notification"} };

	void GLAPIENTRY message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* user_param) {
		fprintf(stderr, "GL::%s::%s::%s\n%s\n\n", debug_source[source], debug_type[type], debug_severity[severity], message);
	}

	void debug_callback() {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(message_callback, nullptr);
	}
#else
	void debug_callback() {}
#endif

}