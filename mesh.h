#ifndef MESH_H
#define MESH_H

#ifndef GLEW_STATIC
    #define GLEW_STATIC
#endif
#include <GL/glew.h>

#include "shader.h"
#include "loadtexture.h"

struct Texture {
    std::string path;
    GLuint id;
};

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 UV;
    GLushort Tex;
};

class Mesh
{
public:
    
    Mesh(GLfloat * positions, GLfloat * normals, GLfloat * UVs, GLuint * indices, int32_t numindices, std::vector<std::string> texpaths);
    ~Mesh() {}
    
    void render(Shader * shader);

private:
    
    GLuint VAO, VBO;
    
    GLfloat * position_data;
    GLfloat * normal_data;
    GLfloat * UV_data;
    GLuint * index_data;
    int32_t num_indices;
    GLushort num_texs;
    
    glm::mat4 model_mat;
    
    std::vector<Texture> textures;
    std::vector<Vertex> vertices;

};

Mesh::Mesh(GLfloat * positions, GLfloat * normals, GLfloat * UVs, GLuint * indices, int32_t numindices, std::vector<std::string> texpaths)
{
    this->position_data = positions;
    this->normal_data = normals;
    this->UV_data = UVs;
    this->index_data = indices;
    this->num_indices = numindices;
    this->num_texs = (GLushort)texpaths.size();
    this->model_mat = glm::mat4(1.0f);
    
    for(int i = 0; i < this->num_texs; i++)
    {
        Texture tex;
        tex.path = texpaths[i];
        tex.id = AlphaTextureFromFile(texpaths[i].c_str(), false);
        
        this->textures.push_back(tex);
    }
    
    for(int32_t i = 0; i < this->num_indices; i++)
    {
        Vertex vertex;
        
        vertex.Position = glm::vec3(*(this->position_data + 3 * index_data[4*i]), 
                                    *(this->position_data + 3 * index_data[4*i] + 1),
                                    *(this->position_data + 3 * index_data[4*i] + 2));
        
        vertex.Normal = glm::vec3(*(this->normal_data + 3 * index_data[4*i + 1]), 
                                    *(this->normal_data + 3 * index_data[4*i + 1] + 1),
                                    *(this->normal_data + 3 * index_data[4*i + 1] + 2));
        
        vertex.UV = glm::vec2(*(this->UV_data + 2 * index_data[4*i + 2]), 
                                    *(this->UV_data + 2 * index_data[4*i + 2] + 1));
        
        vertex.Tex = (GLushort)*(this->indices[4*i + 3]);
        
        this->vertices.push_back(vertex);
    }
    
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    
    glBindVertexArray(this->VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);    
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribPointer(0);
    glVertexAttribPoonter(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    
    glEnableVertexAttribPointer(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
    
    glEnableVertexAttribPointer(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, UV));
    
    glEnableVertexAttribPointer(3);
    glVertexAttribIPointer(3, 1, GL_UNSIGNED_SHORT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Tex));
    
    glBindVertexArray(0);
}

void Mesh::render(Shader * shader)
{
    this->model_mat = glm::mat4(1.0f);
    
}

#endif
