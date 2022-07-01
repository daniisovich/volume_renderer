#pragma once

#include <string>

#include "gl_texture3d.h"


namespace utility {

	glTexture3D loadVolume(const std::string_view path);

}