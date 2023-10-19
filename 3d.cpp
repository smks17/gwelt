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


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


int main () {
    GW::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
       std::cout << "Failed to initialize GLAD" << std::endl;
       return -1;
    }

    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };
    GW::BufferData * vertices_data = new GW::BufferData{(void *)vertices, sizeof(vertices), 3};
    GW::Buffer *VBO = new GW::Buffer(vertices_data);

    float tex_coords[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,

        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,

        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f
    };
    GW::BufferData * tex_coords_data = new GW::BufferData{(void *)tex_coords, sizeof(tex_coords), 2};
    GW::Buffer *VBO_tex_coord = new GW::Buffer(tex_coords_data);

    GW::VertexArray VAO;
    VAO.add_buffer(VBO, 0);
    VAO.add_buffer(VBO_tex_coord, 1);

    glm::vec3 cube_pos[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3( 1.0f, -2.0f, -2.5f),
        glm::vec3( -2.5f, 1.0f, -5.0f),
    };

    GW::Texture texture;
    if (!texture.load("resources/smile.jpg", GL_REPEAT, GL_REPEAT))
        std::cerr << "ERROR: Texture could not load proparely" << std::endl;

    GW::Shader shader("resources/vertexShader.glsl", "resources/fragmentShader.glsl");

    shader.set_int("texture", 0);

    while (!window.is_closed()) {
        window.process_input();

        GW::color_screen(0.18f, 0.18f, 0.18f, 1.0f);

        // view
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        // projection
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.001f, 100.0f);

        shader.set_4_matrix_float("view", glm::value_ptr(view));
        shader.set_4_matrix_float("projection", glm::value_ptr(projection));

        texture.active_and_bind();

        shader.use();

        VAO.bind();
        for(unsigned int i = 0 ; i < 4 ; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cube_pos[i]);
            float angle = 3.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.set_4_matrix_float("model", glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        VAO.unbind();

        window.swap_buffer();
        window.poll_events();
    }

    shader.delete_shader();

    std::cout << "Finish" << std::endl;
    return 0;
}
