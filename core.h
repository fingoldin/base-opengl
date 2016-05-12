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
    
    void begin(const char * winName, GLfloat * inVertices, GLfloat * inIndices);
    
    void end(void);
    
    void update(void);
    
    void render(void);
    
    void clearScreen(void)
    
    void updateScreen(void);
    
    Core() {}
    ~Core() {}
    
    Vertex getVertexOfIndex(GLuint index) { return this->vertices[index]; }
    
    
private:
    
    void init_gl(void);
    
    friend class InputHandler; 
    InputHandler * input_handler;
    
    GLfloat vertex_data;
    GLfloat index_data;
    
    int gl_context_version_major,
        gl_context_version_minor,
        gl_samples,
        gl_opengl_profile,
        gl_resizable,
        gl_opengl_forward_compat,
        
        viewport_x,
        viewport_y,
        viewport_w,
        viewport_h;
    
    GLuint window_width,
           window_height;
    
    std::string window_name;
    
    GLFWmonitor * window_monitor;
    GLFWwindow * window_share;
    GLFWwindow * window;
};

void Core::begin(const char * winName, GLfloat * inVertices, GLuint * inIndices)
{
    this->vertex_data = inVertices;
    this->index_data = inIndices;
    
    this->gl_context_version_major = 3;
    this->gl_context_version_minor = 3;
    this->gl_samples = 8;
    this->gl_opengl_profile = GL_OPENGL_CORE_PROFILE;
    this->gl_resizable = GL_FALSE;
    this->gl_opengl_forward_compat = GL_TRUE;
    
    this->window_width = 900;
    this->window_height = 600;
    this->viewport_x = 0;
    this->viewport_y = 0;
    this->viewport_w = this->window_width;
    this->viewport_h = this->window_height;
    
    this->window_name = winName;
    
    this->window_monitor = NULL;
    this->window_share = NULL;
    this->window = NULL;
    
    this->input_handler = (InputHandler*)malloc(sizeof(InputHandler));
    
    this->init_gl();
}

void Core::init_gl(void)
{
    if(glfwInit() != GL_TRUE) {
        std::printf("\nERROR in Core::init_gl(void): could not initialize GLFW!\n");
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->gl_context_version_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->gl_context_version_minor);
    glfwWindowHint(GLFW_SAMPLES, this->gl_samples);
    glfwWindowHint(GLFW_OPENGL_PROFILE, this->gl_opengl_profile);
    glfwWindowHint(GLFW_RESIZABLE, gl_resizable);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, this->gl_opengl_forward_compat);
    
    this->window = glfwCreateWindow(this->window_width, 
                                    this->window_height, 
                                    this->window_name.c_str(), 
                                    this->window_monitor, 
                                    this->window_share
    );
    glfwMakeContextCurrent(this->window);
    
    this->input_handler->begin(this->window);
    
    this->init_vertices();
    
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    glViewport(this->viewport_x, this->viewport_y, this->viewport_w, this->viewport_h);
    
    glEnable(GL_DEPTH_TEST);
    
    Shader shader("shader.vs", "shader.frag");
}

void Core::clearScreen(void) {
    glClearColor(this->clear_color[0], this->clear_color[1], this->clear_color[2], this->clear_color[3]);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
}
     

#endif
