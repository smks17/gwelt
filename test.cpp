#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <time.h>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "ThirdParty/stb_image.h"


#define UNREFERENCED_PARAMETER(x) x


#define WIDTH  800
#define HEIGHT 600


unsigned int VAO[2], VBO[2], EBO;
unsigned int shader_program;


const char *load_shader_source(const char * filename){
    std::ifstream file(filename, std::ios::in);
    if (!file.is_open()){
        std::cerr << "ERROR: shader file does not exist: " << filename << std::endl;
        // exit(1);
    }
    file.seekg(0,std::ios::end);
    size_t length = static_cast<size_t>(file.tellg());
    file.seekg(0,std::ios::beg);

    char * buffer = new char[length+1];
    file.read(&buffer[0],length);
    buffer[length] = 0;
    file.close();

    std::cout << buffer << std::endl;

    return buffer;
}


void frameBufferCallback(GLFWwindow* window, int width, int height) {
    UNREFERENCED_PARAMETER(window);
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    // else if (glfwGetKey(window, GLFW_KEY_F5) == GLFW_PRESS)
    //     shader_program = render_thing();
}


int main() {
    // init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "test", NULL, NULL);
    if (window == NULL) {
        std::cerr << "ERROR: Could not create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Glad init
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
       std::cout << "Failed to initialize GLAD" << std::endl;
       return -1;
    }

    glfwSetFramebufferSizeCallback(window, frameBufferCallback);

    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    const char *vertex_shader_source = load_shader_source("resources/vertexShader.glsl");
    // const char *vertex_shader_source = "#version 330 core\n"
    //     "layout (location = 0) in vec3 aPos;\n"
    //     "void main() {\n"
    //     "gl_Position = vec4(aPos, 1.0);\n"
    //     "}";
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    int  success;
    char infoLog[512];

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        std::cout << "ERROR: vertex shader compilation failed: " << infoLog << std::endl;
    }

    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragment_shader_source = load_shader_source("resources/fragmentShader.glsl");
    // const char *fragment_shader_source = "#version 330 core\n"
    //     "out vec4 FragColor;\n"
    //     "void main() {\n"
    //     "FragColor = vec4(1.0f, 0.18f, 0.18f, 1.0f);\n"
    //     "}\0";
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
        std::cout << "ERROR: fragment shader compilation failed: " << infoLog << std::endl;
    }

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glGetShaderiv(shader_program, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shader_program, 512, NULL, infoLog);
        std::cout << "ERROR: fragment shader compilation failed: " << infoLog << std::endl;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // float vertices[] = {
    //     // cordinates        // colors          // texture coords
    //     -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,          // left top
    //     -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,          // left bottom
    //     0.5f ,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,          // right top
    //     0.5f , -0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f           // right bottom
    // };

    float vertices[] = {
        -0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f ,  0.5f, 0.0f,
        0.5f , -0.5f, 0.0f
    };

    float colorA[] = {
        0.0f, 1.0f, 0.0f
        1.0f, 0.0f, 0.0f
        0.0f, 0.0f, 1.0f
    };

    float colorB[] = {
        1.0f, 0.0f, 0.0f
        0.0f, 0.0f, 1.0f
        1.0f, 1.0f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3
    };

    glGenVertexArrays(1, &VAO[0]);
    glGenBuffers(1, &VBO[0]);
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorA), &colorA, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
    // glEnableVertexAttribArray(2);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // unsigned int texture;
    // glGenTextures(1, &texture);
    // glBindTexture(GL_TEXTURE_2D, texture);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // int width, height, channels;
    // stbi_set_flip_vertically_on_load(true);
    // unsigned char *data = stbi_load("resources/smile.jpg", &width, &height, &channels, 0);
    // if (!data) {
    //     std::cerr << "ERROR: Could not load texture" << std::endl;
    // }
    // else {
    //     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    //     glGenerateMipmap(GL_TEXTURE_2D);
    // }
    // stbi_image_free(data);

    // glUseProgram(shader_program);
    // glUniform1i(glGetUniformLocation(shader_program, "texture"), 0);

    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.18f, 0.18f, 0.18f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // transform
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::rotate(transform, static_cast<float>(glfwGetTime()), glm::vec3(1.0f, 0.0f, 0.0f));
        // transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));
        unsigned int transform_loc = glGetUniformLocation(shader_program, "transform");
        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform));

        // glActiveTexture(GL_TEXTURE);
        // glBindTexture(GL_TEXTURE_2D, texture);

        glUseProgram(shader_program);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(0, &VAO);
    glDeleteBuffers(0, &VBO);
    glfwTerminate();
    return 0;
}
