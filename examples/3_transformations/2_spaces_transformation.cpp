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

    Shader vert1("shader/perspective_shader.vert", GL_VERTEX_SHADER);
    Shader frag1("shader/fragment.frag", GL_FRAGMENT_SHADER);
    ShaderProgram sprog1({vert1,frag1});
    sprog1.link();
    vert1.del();
    frag1.del();

    std::vector<float> vertices = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
    std::vector<int> indices = {};

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
    GLuint64 shiftwidth = 5;
    vao1.set(0,3,shiftwidth,0);
    vao1.enable(0);
    vao1.set(1,2,shiftwidth,3);
    vao1.enable(1);
//     glBindVertexArray(0);




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
        vao1.bind();
        sprog1.use();
        sprog1.setUniform1i("box",0);
        sprog1.setUniform1i("awesome",1);
        sprog1.setUniform1i("kappa",2);


        int x = 10;
        int y = 10;
        float currentTime = glfwGetTime();
        float fac = 0;
        float fac2 = 0;

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f,0.0f,0.0f));
        model = glm::rotate(model, glm::radians(currentTime*50), glm::vec3(0.0f,0.0f,1.0f));
        model = glm::rotate(model, glm::radians(currentTime*250), glm::vec3(0.0f,1.0f,0.0f));

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);

        sprog1.setUniformMatrix("model", model);
        sprog1.setUniformMatrix("view", view);
        sprog1.setUniformMatrix("projection", projection);

        glDrawArrays(GL_TRIANGLES, 0, 36);
//         glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
