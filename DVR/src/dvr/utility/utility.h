#pragma once
#include "dvr/gl/texture/gl_texture3d.h"


namespace dvr::utility {

	gl::Texture3D loadVolume(const std::string_view path);

}