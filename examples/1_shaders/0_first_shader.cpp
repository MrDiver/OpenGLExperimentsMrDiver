#include <chrono>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include <Shader.hpp>
#include <ShaderProgram.hpp>

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

bool hold = false;
bool wireframe = false;
void toggleWireframe(GLFWwindow *window)
{
    /* Wireframe Mode */
    if (hold && glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
    {
        hold = false;
    }
    if (!hold && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        if (wireframe)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        wireframe = !wireframe;
        hold = true;
    }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(640, 480, "Test1", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 640, 480);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    ShaderProgram sprog1;
    {
        Shader vert1("vertex.vert", GL_VERTEX_SHADER);
        Shader frag1("fragment.frag", GL_FRAGMENT_SHADER);
        sprog1.attach(vert1);
        sprog1.attach(frag1);
        sprog1.link();
    }

    float vertices[] = {
        -1.0f, -0.5f, // 1 bottom left
        0.3f, -0.0f,  // 1 bottom right
        -0.5f, 0.5f,  // 1 top
        0.0f, 0.0,    // last
    };

    int indices[] = {0, 1, 2};

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        toggleWireframe(window);

        //Get time
        auto current_time = std::chrono::high_resolution_clock::now();
        float time = glfwGetTime();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        sprog1.use();
        sprog1.setUniform2f("positionOffset", sin(time),cos(time)/10);
        sprog1.setUniform3f("colorChange", (sin(time)+1)/2,(cos(time)+1)/2, (sin(time/2)+1)/2);
        glDrawElements(GL_TRIANGLES, 4, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
