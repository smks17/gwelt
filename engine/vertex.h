#ifndef GW_VERTEX_H
#define GW_VERTEX_H

#include <vector>

#include "gwelt.h"
#include "buffer.h"

namespace GW {

class VertexArray{
protected:
    unsigned m_vertex_array;
    std::vector<Buffer *> m_buffers;  // TODO: Do not use vector
public:
    VertexArray();
    ~VertexArray();

    void add_buffer(Buffer *buffer, unsigned int);

    inline void bind () const {
        glBindVertexArray(m_vertex_array);
    }

    inline void unbind () const {
        glBindVertexArray(0);
    }
};

};

#endif // GW_VERTEX_H
