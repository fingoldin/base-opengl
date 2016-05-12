#ifndef CORE_H
#define CORE_H

#include <cstdlib>
#include <cstdio>

#include <string>
#include <vector>
#include <cmath>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transformation.hpp>

#include "inputhandler.h"

struct Vertex {
    glm::vec3 Position;
    
    glm::vec3 Normal;
    
    glm::vec2 UV;
    
    GLuint Texture;
};


class Core
{
public:
    
    void begin(void);
    
    void end(void);
    
    void update(void);
    
    void render(void);
    
    void clearScreen(void)
    
    void updateScreen(void);
    
    Core() {}
    ~Core() {}
    
    Vertex getVertexOfIndex(GLuint index) { return this->vertices[index]; }
    
    
private:
    
    friend class InputHandler; 
    InputHandler * inputHandler;
    
    std::vector<Vertex> vertices;    
    
    int gl_context_version_major,
        gl_context_version_minor,
        gl_opengl_profile,
        gl_samples,
        gl_resizable,
        gl_opengl_forward_compat;
};


void Core::begin(void)
{
    glfwInit();
}

void Core::clearScreen(void) {
    glClearColor(this->clear_color[0], this->clear_color[1], this->clear_color[2], this->clear_color[3]);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
}
    

#endif
