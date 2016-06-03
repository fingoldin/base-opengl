#ifndef MESH_H
#define MESH_H

#ifndef GLEW_STATIC
    #define GLEW_STATIC
#endif
#include <GL/glew.h>

#include "shader.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
};

class Mesh
{
public:
    
    Mesh(tinyobj::shape_t &shape);
    ~Mesh() {}
    
    void render(Shader * shader);

private:
    
    GLuint VAO, VBO, EBO;
    
    std::string name;
    
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

};

Mesh::Mesh(tinyobj::shape_t &shape)
{
    assert((shape.mesh.indices.size() % 3) == 0);
	
    this->name = shape.name;
	
    for(size_t f = 0; f < shape.mesh.positions.size() / 3; f++) {
        Vertex v;
        v.Position = glm::vec3(shape.mesh.positions[3*f], shape.mesh.positions[3*f+1], shape.mesh.positions[3*f+2]);
        this->vertices.push_back(v);
    }
    if(shape.mesh.normals.size() > 0) {
        for(size_t f = 0; f < shape.mesh.normals.size() / 3; f++) {
            this->vertices[f].Normal = glm::vec3(shape.mesh.normals[3*f], shape.mesh.normals[3*f+1], shape.mesh.normals[3*f+2]);
        }
    }
    
    this->indices = shape.mesh.indices;
    
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);
    
    glBindVertexArray(this->VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);    
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribPointer(0);
    glVertexAttribPoonter(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    
    glEnableVertexAttribPointer(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
    
    glBindVertexArray(0);
}

void Mesh::render(Shader * shader)
{
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

#endif
