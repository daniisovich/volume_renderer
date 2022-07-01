#include "utility.h"

#include <fstream>
#include <sstream>
#include <array>
#include <algorithm>
#include <iostream>

struct VolumeInfo {
	std::string filename{ "" };
	std::array<uint32_t, 3> size;
	GLenum type{ 0 };
	GLenum format{ 0 };
};

VolumeInfo parseMetadata(const std::string_view path);
void parseLine(const std::string& line, VolumeInfo& info);

namespace utility {

	glTexture3D loadVolume(const std::string_view path) {

		VolumeInfo volume_info{ parseMetadata(path) };

		return glTexture3D{ volume_info.format, volume_info.size };
	}
	

}

VolumeInfo parseMetadata(const std::string_view path) {

	std::ifstream file{ path.data(), std::ios::binary };
	if (!file)
		throw std::runtime_error("Failed to open file " + std::string(path));

	VolumeInfo volume_info;

	for (std::string line; std::getline(file, line);) {
		parseLine(line, volume_info);
	}

	return volume_info;

}

void parseLine(const std::string& line, VolumeInfo& info) {

	std::string key, value;
	std::stringstream line_stream{ line };
	std::getline(line_stream, key, ':');
	std::getline(line_stream, value, ':');

	value.erase(std::remove(value.begin(), value.end(), '\t'), value.end());
	value.erase(std::remove(value.begin(), value.end(), '\r'), value.end());

	if (key == "ObjectFileName") {
		info.filename = value;
	} else if (key == "Resolution") {
		std::stringstream value_stream{ value };
		for (int i{ 0 }; i < 3; ++i) {
			std::string part;
			std::getline(value_stream, part, ' ');
			info.size[i] = std::stoi(part);
		}
	}
	else if (key == "Format") {
		if (value == "UCHAR")
			info.type = GL_UNSIGNED_BYTE;
	}
	else if (key == "ObjectModel") {
		if (value == "RGBA")
			info.format = GL_RGBA;
	}

}