#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>
#include "shader.h"

using namespace std;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

int main () {


/*

    Initialize GLFW

*/

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
/*

    Create GLFW Window

*/

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Michael Ross - CS330 3.3", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

/*

    GLAD: Load all OpenGL Function Pointers

*/
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    glEnable(GL_DEPTH_TEST); 

    // Build and compile shaders
    // uses custom include to make creating new shaders easier.
    Shader myShader("../shaders/default.vs", "../shaders/default.fs");

    // Setup vertex data and configure vertex attributes
    float triangleVertices1[] = {
        -0.5f, 0.0f, 0.0f, 1.0f, 0.8f, 0.9f,    // a
        0.0f, 1.0f, -0.5f, 1.0f, 1.0f, 1.0f,    // b
        0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,     // c
        0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,    // d
        -0.5f, 0.0f, -1.0f, 0.0f, 0.5f, 0.5f   // e
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 1, 3,
        3, 1, 4,
        4, 1, 0,
        0, 2, 3,
        0, 4, 3
    };
    /*
    A = -0.5f, 0.0f, 0.0f, 1.0f, 0.8f, 0.9f,
    B = 0.0f, 1.0f, -0.5f, 1.0f, 1.0f, 1.0f,
    C = 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    D = 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    E = -0.5f, 0.0f, -1.0f, 0.0f, 0.5f, 0.5f,

    a, b, c
    c, b, d
    d, b, e
    e, b, a
    */

    // Create the model matrix:
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    // Create the view matrix:
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 

    // Create the projection matrix
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


    // Initialize the vertex buffer objects
    unsigned int VBO, VAO, EBO;

    // Generate one vertex array
    glGenVertexArrays(1, &VAO);

    // Generate one vertex and element buffers
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Bind the VBO buffer to the GL_ARRAY_BUFFER buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // **Bind the EBO buffer to ELEMENT_ARRAY_BUFFER object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // Add the triangle vertices to the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices1), triangleVertices1, GL_STATIC_DRAW);

    // **Add the index data to the buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Describe where to find the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float))); // color
    glEnableVertexAttribArray(1);


    // glUseProgram(shaderProgram);

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 10.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        myShader.setMatrix4fv("model", model);
        myShader.setMatrix4fv("view", view);
        myShader.setMatrix4fv("projection", projection);
        myShader.use();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 12);
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
        glfwPollEvents();    
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;

}
