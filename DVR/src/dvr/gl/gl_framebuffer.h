#pragma once

#include "dvr/gl/texture/gl_texture2d.h"


namespace dvr::gl {

	class Framebuffer {

	public:

		Framebuffer(GLenum format, const std::array<uint32_t, 2>& size, uint32_t attachment, uint32_t mipmap_level);

		Framebuffer() = delete;
		Framebuffer(const Framebuffer&) = delete;
		Framebuffer& operator=(const Framebuffer&) = delete;
		~Framebuffer() = default;

		Framebuffer(Framebuffer&& other) noexcept;
		Framebuffer& operator=(Framebuffer&& other) noexcept;

		inline void activateTexture(GLuint texture_unit) const { m_attachment.activate(texture_unit); }
		inline void bind() const { glBindFramebuffer(GL_FRAMEBUFFER, m_id.value); }
		inline void unbind() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

	private:

		struct ID {
			ID() { glCreateFramebuffers(1, &value); }
			~ID() { release(); }
			void release() { glDeleteFramebuffers(1, &value); value = 0; }
			uint32_t value;
		} m_id;

		Texture2D m_attachment;

	};

}
