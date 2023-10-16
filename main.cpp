#include <iostream>

#include "engine/gwelt.h"

#include "engine/buffer.h"
#include "engine/shader.h"
#include "engine/texture.h"
#include "engine/vertex.h"
#include "engine/window.h"


#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE  "gwelt"


int main () {
    GW::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
       std::cout << "Failed to initialize GLAD" << std::endl;
       return -1;
    }

    float vertices[] = {
        -0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f ,  0.5f, 0.0f,
        0.5f , -0.5f, 0.0f
    };
    GW::BufferData * vertices_data = new GW::BufferData{(void *)vertices, sizeof(vertices), 3};
    GW::Buffer *VBO = new GW::Buffer(vertices_data);

    float color[] = {
        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f
    };
    GW::BufferData * color_data = new GW::BufferData{(void *)color, sizeof(color), 3};
    GW::Buffer *VBO_color = new GW::Buffer(color_data);

    float tex_coords[] = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };
    GW::BufferData * tex_coords_data = new GW::BufferData{(void *)tex_coords, sizeof(tex_coords), 2};
    GW::Buffer *VBO_tex_coord = new GW::Buffer(tex_coords_data);

    unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3
    };
    GW::BufferData * IBO = new GW::BufferData{(void *)indices, sizeof(indices), 6};
    GW::IndexBuffer EBO(IBO);

    GW::VertexArray VAO;
    VAO.add_buffer(VBO, 0);
    VAO.add_buffer(VBO_color, 1);
    VAO.add_buffer(VBO_tex_coord, 2);

    GW::Texture texture;
    if (!texture.load("resources/smile.jpg", GL_REPEAT, GL_REPEAT))
        std::cerr << "ERROR: Texture could not load proparely" << std::endl;

    GW::Shader shader("resources/vertexShader.glsl", "resources/fragmentShader.glsl");

    shader.set_int("texture", 0);

    while (!window.is_closed()) {
        window.process_input();

        GW::color_screen(0.18f, 0.18f, 0.18f, 1.0f);

        // transform
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::rotate(transform, static_cast<float>(glfwGetTime()), glm::vec3(1.0f, 0.0f, 0.0f));
        shader.set_4_matrix_float("transform", glm::value_ptr(transform));

        texture.active_and_bind();

        shader.use();

        VAO.bind();
        EBO.bind();
        glDrawElements(GL_TRIANGLES, EBO.get_component(), GL_UNSIGNED_INT, 0);
        EBO.unbind();
        VAO.unbind();

        window.swap_buffer();
        window.poll_events();
    }

    shader.delete_shader();

    std::cout << "Finish" << std::endl;
    return 0;
}
