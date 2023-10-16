#include <iostream>
#include <fstream>

#include "shader.h"

namespace GW {

Shader::Shader(const char* vertex_source, const char * fragment_source):
m_vertex_source(vertex_source), m_fragment_source(fragment_source) {
    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    int success;
    char error[512];

    const char * vertex_shader_source = read_shader_source(m_vertex_source);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertex_shader, 512, NULL, error);
        std::cout<<"ERROR: Vertex SHADER: " << error << std::endl;
    }
    std::cout << "INFO : vertexShader is compiled!" << std::endl;

    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char * fragment_shaderSource = read_shader_source(m_fragment_source);
    glShaderSource(fragment_shader, 1, &fragment_shaderSource, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragment_shader, 512, NULL, error);
        std::cout<<"ERROR Vertex SHADER: " << error << std::endl;
    }
    std::cout << "INFO : fragment_shader is compiled!" << std::endl;

    // link the m_shader_id
    m_shader_id = glCreateProgram();
    glAttachShader(m_shader_id, vertex_shader);
    glAttachShader(m_shader_id, fragment_shader);
    glLinkProgram(m_shader_id);

    glGetProgramiv(m_shader_id, GL_LINK_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragment_shader, 512, NULL, error);
        std::cout<<"ERROR: SHADER LINK: " << error << std::endl;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

const char * Shader::read_shader_source(const char * source) {
    std::ifstream file(source, std::ios::in);
    if (!file.is_open()){
        std::cerr << "ERROR: shader file does not exist: " << source << std::endl;
        return nullptr;
    }
    file.seekg(0, std::ios::end);
    unsigned int length = static_cast<unsigned int>(file.tellg());
    file.seekg(0, std::ios::beg);

    char * buffer = new char[length + 1] {0};
    file.read(&buffer[0], length);
    file.close();

    return buffer;
}

Shader::~Shader() {
    delete_shader();
}

void Shader::use() {
    glUseProgram(m_shader_id);
}

void Shader::delete_shader() {
    glDeleteProgram(m_shader_id);
}

Shader * Shader::reload(const char* vertex_source, const char * fragment_source) {
    // deleteShader();
    Shader * new_shader = new Shader(vertex_source, m_fragment_source);
    new_shader->use();
    return new_shader;
}

void Shader::set_bool(const char *name, bool value) {
    glUniform1i(glGetUniformLocation(m_shader_id, name), value);
}

void Shader::set_int(const char *name, int value) {
    glUniform1i(glGetUniformLocation(m_shader_id, name), value);
}

void Shader::set_float(const char *name, float value) {
    glUniform1f(glGetUniformLocation(m_shader_id, name), value);
}

// void Shader::set_2_int(const char *name, int value1, int value2) {
//     glUniform2i(glGetUniformLocation(m_shader_id, name), value1, value2);
// }

// void Shader::set_2_float(const char *name, float value1, float value2) {
//     glUniform2f(glGetUniformLocation(m_shader_id, name), value1, value2);
// }

// void Shader::set_3_int(const char *name, int value1, int value2, int value3) {
//     glUniform3i(glGetUniformLocation(m_shader_id, name), value1, value2, value3);
// }

// void Shader::set_3_float(const char *name, float value1, float value2, float value3) {
//     glUniform3f(glGetUniformLocation(m_shader_id, name), value1, value2, value3);
// }

// void Shader::set_4_int(const char *name, int value1, int value2, int value3, int value4) {
//     glUniform4i(glGetUniformLocation(m_shader_id, name), value1, value2, value3, value4);
// }

// void Shader::set_4_float(const char *name, float value1, float value2, float value3, float value4) {
//     glUniform4f(glGetUniformLocation(m_shader_id, name), value1, value2, value3, value4);
// }

void Shader::set_3_matrix_float(const char *name, const float *ptr) {
    glUniformMatrix4fv(glGetUniformLocation(m_shader_id, name), 1, GL_FALSE, ptr);
}

void Shader::set_4_matrix_float(const char *name, const float *ptr) {
    glUniformMatrix4fv(glGetUniformLocation(m_shader_id, name), 1, GL_FALSE, ptr);
}

};
