#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0)/2;\n"
                                     "}\0";

    const char *fragmentShaderSourceOrange = "#version 330 core\n"
                                             "out vec4 FragColor;\n"
                                             "void main(){\n"
                                             "    FragColor = vec4(1.0f, 0.5f, 0.2f, 0.5f);\n"
                                             "}\0";

    const char *fragmentShaderSourceYellow = "#version 330 core\n"
                                             "out vec4 FragColor;\n"
                                             "void main(){\n"
                                             "    FragColor = vec4(1.0f, 1.0f, 0.0f, 0.5f);\n"
                                             "}\0";

    float vertices[] = {
        -1.0f, -0.5f, 0.0f, // 1 bottom left
        0.3f, -0.0f, 0.0f,  // 1 bottom right
        -0.5f, 0.5f, 0.0f,  // 1 top
    };

    float vertices2[] = {
        -0.3f, 0.0f, 0.0f, // 2 bottom left
        1.0f, 0.5f, 0.0f,  // 2 bottom right
        0.5f, -0.5f, 0.0f, // 2 top
    };

    int sizeofTriangle = sizeof(vertices);
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
    std::cout << "Success Compiling" << std::endl;

    /* Generate Buffers */
    GLuint triangleVAOs[2], triangleVBOs[2];
    glGenVertexArrays(2, triangleVAOs);
    glGenBuffers(2, triangleVBOs);

    for (int i = 0; i < 2; i++)
    {
        /* Create VBOs */
        glBindVertexArray(triangleVAOs[i]);
        glBindBuffer(GL_ARRAY_BUFFER, triangleVAOs[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeofTriangle, verts[i], GL_STATIC_DRAW);
        /* Set Vertex Attributes */
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        std::cout << "Success Creating Triangle 1" << std::endl;
    }

    GLuint programs[] = {shaderProgramOrange, shaderProgramYellow};

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        toggleWireframe(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Draw Holy Triangle
        for (int i = 0; i < 2; i++)
        {
            glUseProgram(programs[i]);
            glBindVertexArray(triangleVAOs[i]);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}