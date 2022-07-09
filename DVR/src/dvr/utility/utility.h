#pragma once

#include <string>

#include "../gl/core/texture/gl_texture3d.h"


namespace dvr {
	namespace utility {

		gl::Texture3D loadVolume(const std::string_view path);

	}
}