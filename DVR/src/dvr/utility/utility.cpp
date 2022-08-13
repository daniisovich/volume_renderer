#include "precompiled/pch.h"
#pragma hdrstop

#include "utility.h"

#include <iterator>


struct VolumeInfo {
	std::string filename{ "" };
	std::array<uint32_t, 3> size;
	GLenum type{ 0 };
	GLenum format{ 0 };
	GLenum internal_format{ 0 };
};


static VolumeInfo parseMetadata(const std::string_view path);
static void getInternalFormat(VolumeInfo& info);
static void parseLine(const std::string& line, VolumeInfo& info);
static std::vector<uint8_t> loadVolumeData(std::string_view path);

namespace dvr::utility {

	gl::Texture3D loadVolume(const std::string_view path) {

		VolumeInfo volume_info{ parseMetadata(path) };
		getInternalFormat(volume_info);

		const std::string base_path{ path.substr(0, path.find_last_of("/") + 1) };
		std::vector<uint8_t> volume{ loadVolumeData(base_path + volume_info.filename) };

		const std::vector<std::pair<GLenum, GLenum>> texture_params{
			{ GL_TEXTURE_MIN_FILTER, GL_LINEAR },
			{ GL_TEXTURE_MAG_FILTER, GL_LINEAR },
			{ GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER },
			{ GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER },
			{ GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER },
		};

		if (volume.size() != volume_info.size[0] * volume_info.size[1] * volume_info.size[2])
			throw std::runtime_error("Data of volume does not match with dimensions");

		return std::move(gl::Texture3D(volume_info.format, volume_info.internal_format, volume_info.size, volume_info.type, volume, texture_params));

	}

}

VolumeInfo parseMetadata(const std::string_view path) {

	std::ifstream file{ path.data() };
	if (!file)
		throw std::runtime_error("Failed to open file " + std::string(path));

	VolumeInfo volume_info;
	volume_info.format = GL_RED;

	for (std::string line; std::getline(file, line);) {
		parseLine(line, volume_info);
	}

	return volume_info;

}

void getInternalFormat(VolumeInfo& info) {

	if (info.type == GL_UNSIGNED_BYTE) {
		if (info.format == GL_RED) {
			info.internal_format = GL_R8;
		}
		else if (info.format == GL_RGBA) {
			info.internal_format = GL_RGBA8;
		}
	}
}

void parseLine(const std::string& line, VolumeInfo& info) {

	std::string key, value;
	std::stringstream line_stream{ line };
	std::getline(line_stream, key, ':');
	std::getline(line_stream, value, ':');

	value.erase(std::remove(value.begin(), value.end(), '\t'), value.end());
	value.erase(std::remove(value.begin(), value.end(), '\r'), value.end());
	value.erase(std::remove(value.begin(), value.end(), '\n'), value.end());

	if (key == "ObjectFileName") {
		info.filename = value;
	} 
	else if (key == "Resolution") {
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

}

std::vector<uint8_t> loadVolumeData(std::string_view path) {

	std::ifstream file{ path.data(), std::ios::binary};
	if (!file)
		throw std::runtime_error("Failed to open file " + std::string(path));

	return std::vector<uint8_t>(std::istreambuf_iterator<char>(file), {});

}