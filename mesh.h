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

class Mesh
{
public:
    
    Mesh(GLfloat * positions, GLfloat * normals, GLfloat * UVs, GLuint * indices, int numtex, std::vector<std::string> texpaths);
    ~Mesh() {}
    
    void render(Shader * shader);

private:
    
    GLuint VAO, VBO;
    
    GLfloat * position_data;
    GLfloat * normal_data;
    GLfloat * UV_data;
    GLuint * index_data;
    
    int num_texs;
    
    std::vector<Texture> textures;

};

Mesh::Mesh(GLfloat * positions, GLfloat * normals, GLfloat * UVs, GLuint * indices, std::vector<std::string> texpaths)
{
    this->position_data = positions;
    this->normal_data = normals;
    this->UV_data = UVs;
    this->index_data = indices;
    
    this->num_texs = texpaths.size();
    
    for(int i = 0; i < this->num_texs; i++)
    {
        Texture tex;
        tex.path = texpaths[i];
        tex.id = AlphaTextureFromFile(texpaths[i].c_str(), false);
        
        this->textures.push_back(tex);
    }
    
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    
    glBindVertexArray(this->VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
}

#endif
