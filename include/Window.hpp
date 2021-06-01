#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

//typedef void (*windowCallback)(GLFWwindow* window);

class Window{
private:
    GLFWwindow* window;
    bool wireframe = false;
    bool w_held = false;

    void toggleWireframe();
    void exitOnClose();
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
public:
    Window(const unsigned int width, const unsigned int height);
    ~Window();
    GLFWwindow* pointer() const;
    int width();
    int height();
    void tick();
    bool shouldClose();
};
