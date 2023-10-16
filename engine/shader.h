#ifndef GW_SHADER_H
#define GW_SHADER_H

#include "gwelt.h"

namespace GW {

class Shader{
private:
    unsigned int m_shader_id;
    const char* m_vertex_source;
    const char * m_fragment_source;

    const char* read_shader_source(const char * source);
public:
    Shader(const char* vertext_source, const char * fragment_source);
    ~Shader();
    void use();
    void delete_shader();
    Shader * reload(const char* vertext_source, const char * fragment_source);
    unsigned int get_id(){ return m_shader_id; }

    void set_bool(const char *name, bool value);
    void set_int(const char *name, int value);
    void set_float(const char *name, float value);

    // void set_2_int(const char *name, int value1, int value2);
    // void set_2_float(const char *name, float value1, float value2);

    // void set_3_int(const char *name, int value1, int value2, int value3);
    // void set_3_float(const char *name, float value1, float value2, float value3);

    // void set_4_int(const char *name, int value1, int value2, int value3, int value4);
    // void set_4_float(const char *name, float value1, float value2, float value3, float value4);

    void set_3_matrix_float(const char *name, const float *ptr);
    void set_4_matrix_float(const char *name, const float *ptr);
};

};

#endif //GW_SHADER_H
