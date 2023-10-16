#include "window.h"

namespace GW {

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


Window::Window(int width, int height, const char* title, bool full_screen):
    m_width(width), m_height(height), m_title(title)
{
    init_window();
    m_monitors = {0};
    if (full_screen) {
        m_monitors.monitors = glfwGetMonitors(&(m_monitors.count));
        if (!m_monitors.monitors) {
            std::cerr << "ERROR: Could not found any monitor!" << std::endl;
            glfwTerminate();
            return;
        }
        m_window = glfwCreateWindow(m_width, m_height, m_title, m_monitors.monitors[0], nullptr);
    } else {
        m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
    }
    if (!m_window) {
        std::cerr << "ERROR: Could not create window" << std::endl;
        return;
    }
    std::cout << "INFO : glfw window has been created!" << std::endl;
    glfwMakeContextCurrent(m_window);
}


void Window::init_window()
{
    glfwInit();
    // extra setting
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    std::cout << "INFO : glfw initilize!" << std::endl;
}


void color_screen(float red, float green, float blue, float alpha) {
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}


};
