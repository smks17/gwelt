#include "object.h"

namespace GW {

void Object::bind() const {
    m_VAO->bind();
    if (m_IBO)
        m_IBO->bind();
}


void Object::unbind() const {
    if (m_IBO)
        m_IBO->unbind();
    m_VAO->unbind();
}


Object2D::Object2D(Point2D **loc, size_t n_point, Color **color, size_t *indices, size_t n_indices) {
    float *vertices = new float[n_point * 3];
    const size_t SIZEOF_VERTICES = (n_point * 3) * sizeof(float);
    for (size_t i = 0 ; i < n_point ; i++) {
        vertices[i*3] = loc[i]->xf;
        vertices[(i*3) + 1] = loc[i]->yf;
        vertices[(i*3) + 2] = 0;
    }
    GW::BufferData * vertices_data = new GW::BufferData{(void *)vertices, SIZEOF_VERTICES, 3};
    GW::Buffer *VBO = new GW::Buffer(vertices_data);

    float *colors = new float[n_point * 4];
    const size_t SIZEOF_COLORS = (n_point * 4) * sizeof(float);
    // TODO: efficient way to get just one color if necessary
    for (size_t i = 0 ; i < n_point ; i++) {
        colors[i*4] = color[i]->rf;
        colors[(i*4) + 1] = color[i]->gf;
        colors[(i*4) + 2] = color[i]->bf;
        colors[(i*4) + 3] = color[i]->af;
    }
    GW::BufferData * colors_data = new GW::BufferData{(void *)colors, SIZEOF_COLORS, 4};
    GW::Buffer *color_VBO = new GW::Buffer(colors_data);

    if (indices) {
        GW::BufferData * indices_data = new GW::BufferData{(void *)indices, n_indices * sizeof(unsigned int), n_indices};
        m_IBO = new GW::IndexBuffer(indices_data);
    }
    m_vertex_number = n_indices;

    m_VAO = new GW::VertexArray;
    m_VAO->add_buffer(VBO, 0);
    m_VAO->add_buffer(color_VBO, 1);
}


Object2D::Object2D(Point2D **loc, size_t n_point, float* tex_coords, unsigned int *indices, size_t n_indices) {
    float *vertices = new float[n_point * 3];
    const size_t SIZEOF_VERTICES = (n_point * 3) * sizeof(float);
    for (size_t i = 0 ; i < n_point ; i++) {
        vertices[i*3] = loc[i]->xf;
        vertices[(i*3) + 1] = loc[i]->yf;
        vertices[(i*3) + 2] = 0;
    }
    GW::BufferData * vertices_data = new GW::BufferData{(void *)vertices, SIZEOF_VERTICES, 3};
    GW::Buffer *VBO = new GW::Buffer(vertices_data);

    const size_t SIZEOF_TEX_COORDS = (n_point * 2) * sizeof(float);
    GW::BufferData * tex_coords_data = new GW::BufferData{(void *)tex_coords, SIZEOF_TEX_COORDS, 2};
    GW::Buffer *tex_coords_VBO = new GW::Buffer(tex_coords_data);

    if (indices) {
        GW::BufferData * indices_data = new GW::BufferData{(void *)indices, n_indices * sizeof(unsigned int), n_indices};
        m_IBO = new GW::IndexBuffer(indices_data);
    }
    m_vertex_number = n_indices;

    m_VAO = new GW::VertexArray;
    m_VAO->add_buffer(VBO, 0);
    m_VAO->add_buffer(tex_coords_VBO, 1);
}


void Object2D::render() const {
    bind();
    if (m_IBO) glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_IBO->get_component()), GL_UNSIGNED_INT, 0);
    else glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_vertex_number));
    unbind();
}



Object3D::Object3D(Point3D **loc, size_t n_point, Color **color, size_t *indices, size_t n_indices) {
    float *vertices = new float[n_point * 3];
    const size_t SIZEOF_VERTICES = (n_point * 3) * sizeof(float);
    for (size_t i = 0 ; i < n_point ; i++) {
        vertices[i*3] = loc[i]->xf;
        vertices[(i*3) + 1] = loc[i]->yf;
        vertices[(i*3) + 2] = loc[i]->zf;
    }
    GW::BufferData * vertices_data = new GW::BufferData{(void *)vertices, SIZEOF_VERTICES, 3};
    GW::Buffer *VBO = new GW::Buffer(vertices_data);

    float *colors = new float[n_point * 4];
    const size_t SIZEOF_COLORS = (n_point * 4) * sizeof(float);
    // TODO: efficient way to get just one color if necessary
    for (size_t i = 0 ; i < n_point ; i++) {
        colors[i*4] = color[i]->rf;
        colors[(i*4) + 1] = color[i]->gf;
        colors[(i*4) + 2] = color[i]->bf;
        colors[(i*4) + 3] = color[i]->af;
    }
    GW::BufferData * colors_data = new GW::BufferData{(void *)colors, SIZEOF_COLORS, 4};
    GW::Buffer *color_VBO = new GW::Buffer(colors_data);

    if (indices) {
        GW::BufferData * indices_data = new GW::BufferData{(void *)indices, n_indices * sizeof(unsigned int), n_indices};
        m_IBO = new GW::IndexBuffer(indices_data);
    }
    m_vertex_number = n_indices;

    m_VAO = new GW::VertexArray;
    m_VAO->add_buffer(VBO, 0);
    m_VAO->add_buffer(color_VBO, 1);
}


Object3D::Object3D(Point3D **loc, size_t n_point, float* tex_coords, unsigned int *indices, size_t n_indices) {
    float *vertices = new float[n_point * 3];
    const size_t SIZEOF_VERTICES = (n_point * 3) * sizeof(float);
    for (size_t i = 0 ; i < n_point ; i++) {
        vertices[i*3] = loc[i]->xf;
        vertices[(i*3) + 1] = loc[i]->yf;
        vertices[(i*3) + 2] = loc[i]->zf;
    }
    GW::BufferData * vertices_data = new GW::BufferData{(void *)vertices, SIZEOF_VERTICES, 3};
    GW::Buffer *VBO = new GW::Buffer(vertices_data);

    const size_t SIZEOF_TEX_COORDS = (n_point * 2) * sizeof(float);
    GW::BufferData * tex_coords_data = new GW::BufferData{(void *)tex_coords, SIZEOF_TEX_COORDS, 2};
    GW::Buffer *tex_coords_VBO = new GW::Buffer(tex_coords_data);

    if (indices) {
        GW::BufferData * indices_data = new GW::BufferData{(void *)indices, n_indices * sizeof(unsigned int), n_indices};
        m_IBO = new GW::IndexBuffer(indices_data);
    }
    m_vertex_number = n_indices;

    m_VAO = new GW::VertexArray;
    m_VAO->add_buffer(VBO, 0);
    m_VAO->add_buffer(tex_coords_VBO, 1);
}


void Object3D::render() const {
    bind();
    if (m_IBO) glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_IBO->get_component()), GL_UNSIGNED_INT, 0);
    else glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_vertex_number));
    unbind();
}


};
