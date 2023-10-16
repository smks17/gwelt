#ifndef GW_WINDOW_H
#define GW_WINDOW_H

#include "gwelt.h"

namespace GW {

void processInput(GLFWwindow *);

class Window {
public:
    Window(int width, int height, const char* title, bool full_screen);
    ~Window() {
        glfwTerminate();
    };
    void swap_buffer() const { glfwSwapBuffers(m_window); }
    void process_input() const { processInput(m_window); }
    inline bool is_closed() const { return glfwWindowShouldClose(m_window); }
    inline void poll_events() const { glfwPollEvents(); }
private:
    void init_window();

    GLFWwindow* m_window;

    const char *m_title;
    int m_width, m_height;

    struct {
        GLFWmonitor** monitors;
        int count;
    } m_monitors;
};


#define RED_COLOR   1.0f, 0.0f, 0.0f, 1.0f
#define GREEN_COLOR 0.0f, 1.0f, 0.0f, 1.0f
#define BLUE_COLOR  0.0f, 0.0f, 1.0f, 1.0f
#define BLACK_COLOR 1.0f, 1.0f, 1.0f, 1.0f
#define WHITE_COLOR 0.0f, 0.0f, 0.0f, 1.0f


// class Color {
// public:
//     float r, g, b, a;

//     Color() = delete;
//     Color(float red, float green, float blue, float alpha): r(red), g(green), b(blue), a(alpha) {}
//     Color(float red, float green, float blue): r(red), g(green), b(blue), a(1.0f) {}

//     static const Color& red() const { Color(1.0f, 0.0f, 0.0f, 1.0f); }
//     static const Color& green() const { Color(0.0f, 1.0f, 0.0f, 1.0f); }
//     static const Color& blue() const { Color(0.0f, 0.0f, 1.0f, 1.0f); }
//     static const Color& black() const { Color(1.0f, 1.0f, 1.0f, 1.0f); }
//     static const Color& white() const { Color(0.0f, 0.0f, 0.0f, 1.0f); }
// };


void color_screen(float red, float green, float blue, float alpha);

};

#endif // GW_WINDOW_H
