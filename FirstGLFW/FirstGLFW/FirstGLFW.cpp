#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "Util.h"

using namespace std;

unsigned int program;

float secondHandColor[] = { 0.0, 0.0, 1.0, 1.0 }; 
float minuteHandColor[] = { 0.0, 1.0, 0.0, 1.0 }; 
float hourHandColor[] = { 1.0, 0.0, 0.0 ,1.0 };
GLint secondHandColorLoc, minuteHandColorLoc, hourHandColorLoc;

float velocitySecondPointer = -3.0f;
float velocityMinutePointer = -0.05f;
float velocityHourPointer = -0.00417;

float currentSecondPointer = 270.0f;
float currentMinutePointer = 270.0f;
float currentHourPointer = 270.0f;

float currentTime = 0.0f;
float timeDifference = 0.0f;
float lastTime = 0.0f;

float speed = 1.0f;


void introduction() {
   
    std::cout << "UTS Grafkom" << std::endl;
    std::cout << " ======================= " << std::endl;
    std::cout << "Anggota : " << std::endl;
    std::cout << "1. Akhdan Fadhilah 211401094" << std::endl;
    std::cout << "2. Harry Sion Tarigan 211401021  " << std::endl;
    std::cout << "3. John Sembiring 211401075  " << std::endl;
    std::cout << "4. Nadya Ridha Oktovani 211401097  "<<std::endl;
    std::cout << "5. Nurul Bintang Andini 211401106  "<<std::endl;
    std::cout << "6. Zwingli Asian Raja 211401130  "<<std::endl;
    std::cout << "\n Instruksi : " << std::endl;
    std::cout << "========================" << std::endl;
    std::cout << " - Tekan 'S' untuk menetapkan ulang waktu(setTime)" << std::endl;
    std::cout << " - Tekan 'C' untuk mengubah warna(changeColor)" << std::endl;
    std::cout << " - Tekan 'Panah Kanan' untuk mempercepat" << std::endl;
    std::cout << " - Tekan 'Panah Kiri' untuk memperlambat" << std::endl;
    std::cout << " - Tekan 'R' untuk Reset manipulasi waktu" << std::endl;
    
}


void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        for (int i = 0; i < 4; i++) {
            secondHandColor[i] = (rand() * 1.0f) / RAND_MAX;
            minuteHandColor[i] = (rand() * 1.0f) / RAND_MAX;
            hourHandColor[i] = (rand() * 1.0f) / RAND_MAX;
        }
        glUniform4f(secondHandColorLoc, secondHandColor[0], secondHandColor[1], secondHandColor[2], secondHandColor[3]);
        glUniform4f(minuteHandColorLoc, minuteHandColor[0], minuteHandColor[1], minuteHandColor[2], minuteHandColor[3]);
        glUniform4f(hourHandColorLoc, hourHandColor[0], hourHandColor[1], hourHandColor[2], hourHandColor[3]);
        std::cout << "Warna Diperbarui."<<std::endl;

    }
    else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        float updatedSecond, updatedMinute, updatedHour;
        std::cout << "Jam : Menit : Detik(Dipisah dengan spasi,contoh 2 20 15)"<< std::endl;
        std::cin >> updatedHour >> updatedMinute >> updatedSecond;
        
        std::cout << "Waktu diperbarui menjadi pukul " << updatedHour << " : " << updatedMinute << " : " << updatedSecond << std::endl;
        updatedHour = updatedHour * 3600;
        updatedMinute = updatedMinute * 60;

        float updatedTime = updatedHour + updatedMinute + updatedSecond;

        glfwSetTime(updatedTime);

    }
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {

        speed *= 2.0;
        cout << "Speed : " << speed << "X \n";

    }
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        speed /= 2.0;
        cout << "Speed : " << speed << "X \n";
    }
    else if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        speed = 1.0;
        cout << "Speed Reset \n ";
    }
}


int main(void)
{
    introduction();
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallBack);

    GLenum err = glewInit();

    float vertices[] = {
        1.0, 1.0,
        -1.0, 1.0,
        -1.0, -1.0,
        1.0,-1.0

    };
    unsigned int indexArray[] = {
       0,1,2,
       0,2,3,
    };

    unsigned int vertexBuffer = 0;
    glGenBuffers(1, &vertexBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(0);


    unsigned int indexBuffer = 0;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indexArray, GL_STATIC_DRAW);

    string vertexString = readFile("vertex.vert");
    string fragmentString = readFile("fragment.frag");

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char* vertexChar = vertexString.c_str();
    const char* fragmentChar = fragmentString.c_str();

    
    glShaderSource(vertexShader, 1, &vertexChar, NULL);
    glShaderSource(fragmentShader, 1, &fragmentChar, NULL);

    
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);


    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glUseProgram(program);

    secondHandColorLoc = glGetUniformLocation(program, "secondHandColor");
    glUniform4f(secondHandColorLoc, secondHandColor[0], secondHandColor[1], secondHandColor[2], secondHandColor[3]);

    minuteHandColorLoc = glGetUniformLocation(program, "minuteHandColor");
    glUniform4f(minuteHandColorLoc, minuteHandColor[0], minuteHandColor[1], minuteHandColor[2], minuteHandColor[3]);

    hourHandColorLoc = glGetUniformLocation(program, "hourHandColor");
    glUniform4f(hourHandColorLoc, hourHandColor[0], hourHandColor[1], hourHandColor[2], hourHandColor[3]);

    GLint currentSecondPointerLoc = glGetUniformLocation(program, "currentSecondPointer");
    GLint currentMinutePointerLoc = glGetUniformLocation(program, "currentMinutePointer");
    GLint currentHourPointerLoc = glGetUniformLocation(program, "currentHourPointer");

    
 
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        currentTime = glfwGetTime();
        timeDifference = speed*(currentTime - lastTime);
        lastTime = currentTime;

        currentSecondPointer += timeDifference * velocitySecondPointer;
        currentMinutePointer += timeDifference * velocityMinutePointer;
        currentHourPointer += timeDifference * velocityHourPointer;


        glUniform1f(currentSecondPointerLoc, currentSecondPointer * 3.14159265f / 180.0f);
        glUniform1f(currentMinutePointerLoc, currentMinutePointer * 3.14159265f / 180.0f);
        glUniform1f(currentHourPointerLoc, currentHourPointer * 3.14159265f / 180.0f);

        /* Render here */

        glClear(GL_COLOR_BUFFER_BIT);
  
 
        glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT,nullptr);
        

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}