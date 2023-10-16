#ifndef GW_TEXTURE_H
#define GW_TEXTURE_H

#include "gwelt.h"

namespace GW {

class Texture {
private:
    unsigned m_texture;

    struct {
        int width, height, channels;
    } image_prop = {0};
public:
    Texture();
    ~Texture() {};

    bool load(const char *texture_file, int texture_wrpa_s, int texture_wrpa_t);

    void bind() const { glBindTexture(GL_TEXTURE_2D, m_texture); }
    void unbind() const { glBindTexture(0, m_texture); }

    void active_and_bind();
};

};

#endif // GW_TEXTURE_H
