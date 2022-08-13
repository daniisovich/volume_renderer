#include "precompiled/pch.h"
#pragma hdrstop

#include "gl_debug.h"


static std::unordered_map<GLenum, const char*> source_strings{ {GL_DEBUG_SOURCE_API, "API"}, {GL_DEBUG_SOURCE_WINDOW_SYSTEM, "WindowSystem"}, {GL_DEBUG_SOURCE_SHADER_COMPILER, "ShaderCompiler"},
		{GL_DEBUG_SOURCE_THIRD_PARTY, "ThirdParty"}, {GL_DEBUG_SOURCE_APPLICATION, "Application"}, {GL_DEBUG_SOURCE_OTHER, "Other"} };

static std::unordered_map<GLenum, const char*> type_strings{ {GL_DEBUG_TYPE_ERROR, "Error"}, {GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR, "Deprecated"}, {GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR, "Undefined"},
	{GL_DEBUG_TYPE_PORTABILITY, "Portability"}, {GL_DEBUG_TYPE_PERFORMANCE, "Performance"}, {GL_DEBUG_TYPE_MARKER, "Marker"}, {GL_DEBUG_TYPE_PUSH_GROUP, "Push Group"},
	{GL_DEBUG_TYPE_POP_GROUP, "Pop Group"}, {GL_DEBUG_TYPE_OTHER, "Other"} };

static std::unordered_map<GLenum, const char*> severity_strings{ {GL_DEBUG_SEVERITY_HIGH, "High"}, {GL_DEBUG_SEVERITY_MEDIUM, "Medium"},
											{GL_DEBUG_SEVERITY_LOW, "Low"}, {GL_DEBUG_SEVERITY_NOTIFICATION, "Notification"} };

namespace dvr::gl::debug {

	void GLAPIENTRY message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* user_param) {
		std::cerr << "GL::" << source_strings[source] << "::" << type_strings[type] << "::" << severity_strings[severity] << "\n" << message << "\n\n";
	}

}