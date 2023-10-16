#ifndef GW_BUFFER_H
#define GW_BUFFER_H

#include "gwelt.h"

namespace GW {

struct BufferData {
    void *data;
    size_t size;
    int number_component;
};


class Buffer {
protected:
    const GLenum m_target = GL_ARRAY_BUFFER;
    BufferData* m_data_buffer;
    unsigned m_buffer;
    explicit Buffer(BufferData* data_buffer, GLenum target);
public:
    Buffer() = delete;
    explicit Buffer(BufferData* data_buffer);
    ~Buffer();

    inline void bind () const {
        glBindBuffer(m_target, m_buffer);
    }

    inline void unbind () const {
        glBindBuffer(m_target, 0);
    }

    inline int get_component() const { return m_data_buffer->number_component; }
};

class IndexBuffer : public Buffer {
protected:
    // const static GLenum target = GL_ELEMENT_ARRAY_BUFFER;
public:
    IndexBuffer(BufferData* data_buffer) : Buffer(data_buffer, GL_ELEMENT_ARRAY_BUFFER) {}
    // using Buffer::Buffer;
};

};

#endif // GW_BUFFER_H
