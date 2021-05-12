#include <chrono>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include <Shader.hpp>
#include <ShaderProgram.hpp>
#include "stb_image.hpp"
#include <glm/mat4x4.hpp>
#include <VertexArray.hpp>
#include <VertexBuffer.hpp>
#include <ElementBuffer.hpp>
#include <Texture2D.hpp>
#include <Window.hpp>
#include <vector>

int main()
{
    Window w(640,480);
    GLFWwindow* window = w.pointer();

    ShaderProgram sprog1;
    {
        Shader vert1("shader/vertex.vert", GL_VERTEX_SHADER);
        Shader frag1("shader/fragment.frag", GL_FRAGMENT_SHADER);
        sprog1.attach(vert1);
        sprog1.attach(frag1);
        sprog1.link();
    }

    std::vector<float> vertices = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };
    std::vector<int> indices = {0,1,3,1,2,3};

    // Load Container Texture
    Texture2D containerTexture("res/container.jpg");
    std::cout << "Loaded Container w:"<<containerTexture.width()<<" h:"<<containerTexture.height()<<" c:"<<containerTexture.channels() << std::endl;
    Texture2D awesomeTexture("res/awesomeface.png", GL_RGBA);
    std::cout << "Loaded Awesome w:"<<awesomeTexture.width()<<" h:"<<awesomeTexture.height()<<" c:"<<awesomeTexture.channels() << std::endl;
    Texture2D kappaTexture("res/kappa.jpg");
    std::cout << "Loaded Kappa w:"<<kappaTexture.width()<<" h:"<<kappaTexture.height()<<" c:"<<kappaTexture.channels() << std::endl;
    glBindTexture(GL_TEXTURE_2D,0);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    VertexArray vao1;
    VertexBuffer vbo1;
    ElementBuffer ebo1;
    vao1.bind();
    vbo1.bind();
    vbo1.bindData(vertices, GL_STATIC_DRAW);
    ebo1.bind();
    ebo1.bindData(indices, GL_STATIC_DRAW);
    GLuint64 shiftwidth = 8;
    vao1.set(0,3,shiftwidth,0);
    vao1.enable(0);
    vao1.set(1,3,shiftwidth,3);
    vao1.enable(1);
    vao1.set(2,2,shiftwidth,6);
    vao1.enable(2);
//     glBindVertexArray(0);

    int i = 0;
    while (!w.shouldClose())
    {
        w.tick();
        //Get time
        float time = glfwGetTime();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        containerTexture.bindTo(2);
        awesomeTexture.bindTo(1);
        kappaTexture.bindTo(0);

        glBindVertexArray(VAO);
        sprog1.use();
        sprog1.setUniform2f("positionOffset", sin(time),cos(time)/10);
        sprog1.setUniform3f("colorChange", (sin(time)+1)/2,(cos(time)+1)/2, (sin(time/2)+1)/2);
        sprog1.setUniform1i("texture1",0);
        sprog1.setUniform1i("texture2",1);
        sprog1.setUniform1i("texture3",2);
        sprog1.setUniform1f("time",time);
        sprog1.setUniform1f("timeVert",time);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
