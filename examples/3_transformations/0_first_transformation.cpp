#include <chrono>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>

#include <Shader.hpp>
#include <ShaderProgram.hpp>
#include <VertexArray.hpp>
#include <VertexBuffer.hpp>
#include <ElementBuffer.hpp>
#include <Texture2D.hpp>
#include <Window.hpp>

#include <vector>

#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

int main()
{
    Window w(640,480);
    GLFWwindow* window = w.pointer();

    Shader vert1("shader/vertex.vert", GL_VERTEX_SHADER);
    Shader frag1("shader/fragment.frag", GL_FRAGMENT_SHADER);
    ShaderProgram sprog1({vert1,frag1});
    sprog1.link();
    vert1.del();
    frag1.del();

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

    VertexArray vao1;
    vao1.bind();
    VertexBuffer vbo1(vertices, GL_STATIC_DRAW);
    ElementBuffer ebo1(indices, GL_STATIC_DRAW);
    GLuint64 shiftwidth = 8;
    vao1.set(0,3,shiftwidth,0);
    vao1.enable(0);
    vao1.set(1,3,shiftwidth,3);
    vao1.enable(1);
    vao1.set(2,2,shiftwidth,6);
    vao1.enable(2);
//     glBindVertexArray(0);





    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
    trans = glm::translate(trans, glm::vec3(0.7f,-0.7f,0));
    float start = glfwGetTime();
    while (!w.shouldClose())
    {
        w.tick();
        //Get time
        float time = glfwGetTime();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        containerTexture.bindTo(0);
        awesomeTexture.bindTo(1);
        kappaTexture.bindTo(2);

        /*
            First Test
         */
        float passedTime = glfwGetTime() - start;
        start += passedTime;
        trans = glm::rotate(trans, glm::radians(passedTime*-100), glm::vec3(0.0f, 0.0f, 1.0f));

        vao1.bind();
        sprog1.use();
        sprog1.setUniform1i("box",0);
        sprog1.setUniform1i("awesome",1);
        sprog1.setUniform1i("kappa",2);
        sprog1.setUniformMatrix("transform", trans);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /*
         Second Test
         */
        float currentTime = glfwGetTime();
        glm::mat4 trans2 = glm::mat4(1.0f);
        trans2 = glm::rotate(trans2, glm::radians((float)(currentTime*-100)), glm::vec3(0.0f, 0.0f, 1.0f));
        trans2 = glm::translate(trans2, glm::vec3(-0.5f,0.5f,0));
        trans2 = glm::scale(trans2, glm::vec3(sin(currentTime)/2, sin(currentTime)/2, 1.0f));
        trans2 = glm::rotate(trans2, glm::radians((float)(currentTime*300)), glm::vec3(0.0f, 0.0f, 1.0f));
        sprog1.setUniformMatrix("transform", trans2);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
