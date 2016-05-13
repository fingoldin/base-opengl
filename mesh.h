#ifndef MESH_H
#define MESH_H

#ifndef GLEW_STATIC
    #define GLEW_STATIC
#endif
#include <GL/glew.h>

#include "shader.h"

class Mesh
{
public:
    
    Mesh(GLfloat * positions, GLfloat * normals, GLfloat * UVs, GLuint * indices, int numtex, 
         const char * tex1, 
         const char * tex2 = NULL, 
         const char * tex3 = NULL, 
         const char * tex4 = NULL,
         const char * tex5 = NULL, 
         const char * tex6 = NULL, 
         const char * tex7 = NULL, 
         const char * tex8 = NULL
    );
    ~Mesh() {}
    
    void render(Shader * shader);

private:
    
    GLfloat * position_data;
    GLfloat * normal_data;
    GLfloat * UV_data;
    GLuint * index_data;
    
    int num_texs;
};

Mesh::Mesh(GLfloat * positions, GLfloat * normals, GLfloat * UVs, GLuint * indices, int numtex,
           const char * tex1, 
           const char * tex2 = NULL, 
           const char * tex3 = NULL, 
           const char * tex4 = NULL,
           const char * tex5 = NULL, 
           const char * tex6 = NULL, 
           const char * tex7 = NULL, 
           const char * tex8 = NULL
);
{
    this->position_data = positions;
    this->normal_data = normals;
    this->UV_data = UVs;
    this->index_data = indices;
    
    this->num_texs = numtex
    
    for(int i = 0; i < this->num_texs; i++)
        this->tex_paths[i] = 

#endif
