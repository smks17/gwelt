#include "vertex.h"

namespace GW {

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_vertex_array);
}
VertexArray::~VertexArray() {
    for (Buffer *buffer : m_buffers) {
        delete buffer;
    }
}

void VertexArray::add_buffer(Buffer *buffer, unsigned index) {
    bind();
    buffer->bind();

    glVertexAttribPointer(index, buffer->get_component(), GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(index);
    m_buffers.insert(m_buffers.begin() + index, buffer);

    buffer->unbind();
    unbind();
}

};
