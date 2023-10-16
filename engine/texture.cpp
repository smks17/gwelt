#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace GW {

Texture::Texture() {
    glGenTextures(1, &m_texture);
}


bool Texture::load(const char *texture_filename, int texture_wrpa_s, int texture_wrpa_t) {
    bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture_wrpa_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture_wrpa_t);

    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    // TODO: should configurable
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(texture_filename,
                                    &image_prop.width,
                                    &image_prop.height,
                                    &image_prop.channels,
                                    0);
    if (!data) {
        return false;
    }

    // TODO: Add later for other type of RGB
    glTexImage2D(GL_TEXTURE_2D,     // GLenum target
                 0,                 // GLint level
                 GL_RGB,            // GLint internalformat
                 image_prop.width,  // GLsizei width
                 image_prop.height, // GLsizei height
                 0,                 // GLint border
                 GL_RGB,            // GLenum format
                 GL_UNSIGNED_BYTE,  // GLenum type
                 data               // const void *pixels
    );
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    unbind();
    return true;
}


void Texture::active_and_bind() {
    glActiveTexture(GL_TEXTURE);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

};
