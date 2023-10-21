#ifndef GW_OBJECT_H
#define GW_OBJECT_H

#include <stdint.h>

#include "commonType.h"
#include "vertex.h"
#include "buffer.h"

namespace GW {

class Object {
protected:
    VertexArray *m_VAO;
    IndexBuffer *m_IBO = nullptr;
    size_t m_vertext_number = 0;
public:
    virtual void render() = 0;
    void bind();
    void unbind();
};


class Object2D : public Object {
public:
    Object2D(Point2D **loc, size_t n_point, Color **color, size_t *indices, size_t n_indices);
    Object2D(Point2D **loc, size_t n_point, float* tex_coords, unsigned int *indices, size_t n_indices);
    void render() override;
};

};

#endif  // GWELT_OBJECT_H
