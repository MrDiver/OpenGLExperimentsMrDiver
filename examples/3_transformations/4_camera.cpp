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
#include <Projection.hpp>
#include <Camera.hpp>

#include <vector>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

glm::vec3 cameraPositionTick(GLFWwindow *window,glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, float dt)
{
    const float cameraSpeed = 4.0f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront * dt;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront * dt;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * dt;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * dt;

    return cameraPos;
}

int main()
{
    Window w(640,480);
    GLFWwindow* window = w.pointer();
    glEnable(GL_DEPTH_TEST);

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

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

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


    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    // Part Camera
    glm::vec3 cameraPos = glm::vec3(0.0f,0.0f,5.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f,0.0f,-1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    Projection proj;
    Camera cam(proj,cameraPos,cameraFront);

    float start = glfwGetTime();
    while (!w.shouldClose())
    {
        w.tick();
        //Get time
        float time = glfwGetTime();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;
        float fac = 0;
        float fac2 = 0;

        // Camera
        float radius = 10.0f;
        cam.moveLocal(glm::vec3(1.0f,0.0f,0.0f)*deltaTime);
        cam.lookAt(glm::vec3(sin(currentTime*10),cos(currentTime*5),0.0f));
        glm::mat4 view = cam.viewOnly();


        float ratio = (float)w.width()/(float)w.height();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), ratio, 0.1f, 100.0f);


        sprog1.setUniformMatrix("view", view);
        sprog1.setUniformMatrix("projection", projection);

        for(unsigned int i = 0; i<10; i++){
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::rotate(model, glm::radians(-55.0f), cubePositions[i]);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, glm::radians(sin(currentTime+i*20)*360+currentTime), glm::vec3(0.0f,0.0f,1.0f));
            model = glm::rotate(model, glm::radians(cos(currentTime+i*10)*260), glm::vec3(0.0f,1.0f,0.0f));
            sprog1.setUniformMatrix("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
//         glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
