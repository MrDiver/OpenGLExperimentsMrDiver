#include <Window.hpp>
#include <stdexcept>

Window::Window(const unsigned int width, const unsigned int height){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(640, 480, "Test1", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    this->window = window;
}

Window::~Window()
{

}

void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::exitOnClose()
{
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(this->window, true);
}

void Window::toggleWireframe()
{
    /* Wireframe Mode */
    if (this->w_held && glfwGetKey(this->window, GLFW_KEY_Z) == GLFW_RELEASE)
    {
        this->w_held = false;
    }
    if (!this->w_held && glfwGetKey(this->window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        this->wireframe = !this->wireframe;
        this->w_held = true;
        if (this->wireframe)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

    }
}

void Window::tick(){
    this->exitOnClose();
    this->toggleWireframe();
}

bool Window::shouldClose(){
    return glfwWindowShouldClose(this->window);
}

GLFWwindow* Window::pointer() const{
    return this -> window;
}

int Window::width()
{
    int width, height;
    glfwGetWindowSize(this->window,&width, &height);
    return width;
}

int Window::height()
{
    int width, height;
    glfwGetWindowSize(this->window,&width, &height);
    return height;
}

