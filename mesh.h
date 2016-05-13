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
    
    Mesh(GLfloat * vertices, GLuint * triangles);
    ~Mesh() {}
    
    void render(Shader * shader);

private:
    
    GLfloat * vertex_data;
    GLfloat * triangle_data;

#endif
