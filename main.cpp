#include <iostream>

#include "engine/gwelt.h"

#include "engine/buffer.h"
#include "engine/commonType.h"
#include "engine/shader.h"
#include "engine/object.h"
#include "engine/texture.h"
#include "engine/vertex.h"
#include "engine/window.h"

#include "engine/gwla/gwla.hpp"


#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE  "gwelt"


int main () {
    GW::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, false);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
       std::cout << "Failed to initialize GLAD" << std::endl;
       return -1;
    }

    GW::Point2D **loc = new GW::Point2D*[4];
    loc[0] = new GW::Point2D(-0.5f,  0.5f);
    loc[1] = new GW::Point2D(-0.5f, -0.5f);
    loc[2] = new GW::Point2D(0.5f ,  0.5f);
    loc[3] = new GW::Point2D(0.5f , -0.5f);

    float tex_coords [] = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3
    };

    GW::Object2D obj(loc, (size_t)4, tex_coords, indices, (size_t)6);

    GW::Texture texture;
    if (!texture.load("resources/smile.jpg", GL_REPEAT, GL_REPEAT))
        std::cerr << "ERROR: Texture could not load properly" << std::endl;

    GW::Shader shader("resources/vertexShader.glsl", "resources/fragmentShader.glsl");

    shader.set_int("texture", 0);

    while (!window.is_closed()) {
        window.process_input();

        GW::color_screen(0.18f, 0.18f, 0.18f, 1.0f);

        // transform
        GW::Mat4 transform(1.0f);
        GW::Vec3 axis(1.0f, 0.0f, 0.0f);
        transform = GW::rotate(transform, static_cast<float>(glfwGetTime()), axis);
        shader.set_4_matrix_float("transform", transform.ptr());

        texture.active_and_bind();
        shader.use();
        obj.render();

        window.swap_buffer();
        window.poll_events();
    }

    shader.delete_shader();

    std::cout << "Finish" << std::endl;
    return 0;
}
