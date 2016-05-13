#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

#include "shader.h"

class Mesh
{
public:
    
    Mesh(GLfloat * vertices, GLuint * triangles);
    ~Mesh() {}
    
    void render(Shader * shader)

private:
    
    GLfloat * vertex_data;
    GLfloat * triangle_data;

#endif
