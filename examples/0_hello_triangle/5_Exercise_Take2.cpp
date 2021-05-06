#include <iostream>
#include <chrono>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

void compileShaderWithError(GLuint shader)
{
    glCompileShader(shader);
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION" << infoLog << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

void linkShaderProgramWithError(GLuint program)
{
    glLinkProgram(program);
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "ERROR::PROGRAM::LINK" << infoLog << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

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

    const char *vertexShaderSource = R"glsl(
                                     #version 330 core
                                     uniform vec3 positionOffset;
                                     layout (location = 0) in vec2 aPos;
                                     in vec3 inColor;
                                     out vec3 Color;
                                     void main()
                                     {
                                        Color = inColor;
                                        gl_Position = vec4(aPos+positionOffset.xy, positionOffset.z, 1.0);
                                     })glsl";

    const char *fragmentShaderSourceOrange = R"glsl(#version 330 core

                                             uniform vec3 triangleColor;
                                             out vec4 FragColor;

                                             void main(){
                                                 FragColor = vec4(triangleColor, 1.0f);
                                             })glsl";

    const char *fragmentShaderSourceYellow = R"glsl(#version 330 core
    
                                             uniform float colorOffset;
                                             in vec3 Color;
                                             out vec4 FragColor;

                                             void main(){
                                                 float r = (sin(Color.x+colorOffset)+1.0f)/2.0f;
                                                 float g = (sin(Color.y+colorOffset/4+3.1f)+1.0f)/2.0f;
                                                 float b = (cos(Color.z+colorOffset)+1.0f)/2.0f;
                                                 FragColor = vec4(r,g,b, 0.5f);
                                             })glsl";

    float vertices[] = {
        -1.0f, -0.5f, // 1 bottom left
        0.3f, -0.0f,  // 1 bottom right
        -0.5f, 0.5f,  // 1 top
    };

    float vertices2[] = {
        -0.3f, 0.0f, 1.0f, 0.0f, 0.0f, // 2 bottom left
        1.0f, 0.5f, 0.0f, 1.0f, 0.0f,  // 2 bottom right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // 2 top
    };

    int sizeofTriangles[] = {sizeof(vertices), sizeof(vertices2)};
    float *verts[] = {vertices, vertices2};

    /* Compile Shaders */
    std::cout << "Compiling Shaders" << std::endl;
    /* Create Shaders */
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    /* Bind sources to shader */
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glShaderSource(fragmentShaderOrange, 1, &fragmentShaderSourceOrange, NULL);
    glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSourceYellow, NULL);
    /* Compile Shaders */
    compileShaderWithError(vertexShader);
    compileShaderWithError(fragmentShaderOrange);
    compileShaderWithError(fragmentShaderYellow);
    /* Create Programs with Shader */
    unsigned int shaderProgramOrange = glCreateProgram();
    glAttachShader(shaderProgramOrange, vertexShader);
    glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    linkShaderProgramWithError(shaderProgramOrange);

    unsigned int shaderProgramYellow = glCreateProgram();
    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    linkShaderProgramWithError(shaderProgramYellow);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderOrange);
    glDeleteShader(fragmentShaderYellow);

    /* Attach uniform */
    GLuint uniColor = glGetUniformLocation(shaderProgramOrange, "triangleColor");
    GLuint colorOffset = glGetUniformLocation(shaderProgramYellow, "colorOffset");
    GLuint positionOffsetOrange = glGetUniformLocation(shaderProgramOrange, "positionOffset");
    GLuint positionOffsetYellow = glGetUniformLocation(shaderProgramYellow, "positionOffset");

    /* Generate Buffers */
    GLuint triangleVAOs[2], triangleVBOs[2];
    glGenVertexArrays(2, triangleVAOs);
    glGenBuffers(2, triangleVBOs);

    for (int i = 0; i < 2; i++)
    {
        /* Create VBOs */
        glBindVertexArray(triangleVAOs[i]);
        glBindBuffer(GL_ARRAY_BUFFER, triangleVAOs[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeofTriangles[i], verts[i], GL_STATIC_DRAW);
        /* Set Vertex Attributes */
        if (i == 0)
        { /*Orange Triangle*/
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
            glEnableVertexAttribArray(0);
        }
        else
        { /*Yellow Triangle*/
            GLint posAttrib = glGetAttribLocation(shaderProgramYellow, "aPos");
            GLint colAttrib = glGetAttribLocation(shaderProgramYellow, "inColor");
            glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
            glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(2 * sizeof(float)));
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
        }
        std::cout << "Success Creating Triangle 1" << std::endl;
    }

    GLuint programs[] = {shaderProgramOrange, shaderProgramYellow};

    auto t_start = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        toggleWireframe(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        auto t_now = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();

        //Draw Holy Triangle
        for (int i = 0; i < 2; i++)
        {
            glUseProgram(programs[i]);
            glBindVertexArray(triangleVAOs[i]);
            if (i == 0)
            {
                glUniform3f(uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);
                glUniform3f(positionOffsetOrange, sin(time) / 4.0f, cos(time) / 4.0f, 0.0f);
            }
            if (i == 1)
            {
                glUniform1f(colorOffset, time * 2);
                glUniform3f(positionOffsetYellow, sin(time) / 4.0f, cos(time * 5) / 4.0f, 0.0f);
            }
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}