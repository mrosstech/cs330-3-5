#ifndef CYLINDER_H
#define CYLINDER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Cylinder
{
public:
    // the program ID
    unsigned int ID;
    int numSlices;
    float height;
    float width;
    float x;
    float y;
    float z;
    vector vertices;
    // constructor gets height and width of the cylinder along with number of slices
    Cylinder(float height, float width, int numSlices);

    // draw the cylinder
    void drawCylinder();

    // set the model, view, and transform matrices for the cylinder
    void setMatrix4fv(const std::string &name, glm::mat4 value) const;

    // Create vertexes for the cylinder
    std::vector<float> creatVertices()

};

std::vector<float> createVertices() {
    vector<float> vertices
    // Push the starting coordinates to the vertex array
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z);

    // Calculate 2 * PI
    GLfloat twicePi = 2.0f * PI;

    // Loop through sectors to create outside vertices
    for (int i = 0; i <= numSlices; i++) {
        this.vertices.push_back(this.x + (this.width * cos(i * twicePi / this.numSlices)));
        this.vertices.push_back(this.y + (this.width * sin(i * twicePi / this.numSlices)));
        this.vertices.push_back(0);
    }
    return vertices;
}

void drawCylinder() {

}