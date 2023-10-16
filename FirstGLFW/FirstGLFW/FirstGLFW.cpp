#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Util.h"

using namespace std;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();

    float vertices[] = {
    //-0.5f, 0.5f,
    //-0.5f, -0.5f,
    //0.5f, -0.5f,
    //0.5f, 0.5f
        -1, 1,
        -1, 0.8,
        0.8, 0.8,
        0.8, 1,
        1, 1,
        1, -1,
        0.8, -1,
        0.8, -0.8,
        -1, -0.8,
        -1, -1,
    };

    unsigned int IndexArr[] = {
        //0,1,2,
        //0,2,3
        0,1,2,
        0,2,3,
        3,6,5,
        3,5,4,
        8,6,7,
        8,9,6,
    };

    unsigned int vertexBuffer = 0;
    glGenBuffers(1, &vertexBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 20,vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    unsigned int indexBuffer = 0;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 18, IndexArr, GL_STATIC_DRAW);

    

    string vertexString = readFile("vertex.vert");
    string fragmentString = readFile("fragment.frag");

    const char* vertexChar = vertexString.c_str();
    const char* fragmentChar = fragmentString.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexChar, NULL);

    glShaderSource(fragmentShader, 1, &fragmentChar, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, nullptr);

        //glColor3f(1.0f, 0.0f, 0.0f);
        //glBegin(GL_TRIANGLES);
        //glClear(GL_COLOR_BUFFER_BIT);
        //glVertex2f(0.0f, 0.5f);
        //glVertex2f(-0.5f, -0.5f);
        //glVertex2f(0.5f, -0.5f);

        //glEnd();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}