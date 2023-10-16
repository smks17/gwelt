#include "buffer.h"

namespace GW {

Buffer::Buffer(BufferData* data_buffer, GLenum target)
    : m_data_buffer(data_buffer), m_target(target) {
        glGenBuffers(1, &m_buffer);
        bind();
        glBufferData(m_target, m_data_buffer->size, m_data_buffer->data, GL_STATIC_DRAW);
        unbind();
}

Buffer::Buffer(BufferData* data_buffer)
    : m_data_buffer(data_buffer){
        glGenBuffers(1, &m_buffer);
        bind();
        glBufferData(m_target, m_data_buffer->size, m_data_buffer->data, GL_STATIC_DRAW);
        unbind();
}

Buffer::~Buffer() {
    glDeleteBuffers(0, &m_buffer);
}


};
