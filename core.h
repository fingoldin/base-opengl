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

struct Vertex {
    glm::vec3 Position;
    
    glm::vec3 Normal;
    
    glm::vec2 UV;
    
    GLuint Texture;
};

class InputHandler
{
public:
    
    void begin(GLFWwindow * window);
    
    void end(void);
    
    void update(void) { glfwPollEvents(); }

private:
    
    GLFWwindow * window;
    
    void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);
    void scroll_callback(GLFWwindow * window, double xoffset, double yoffset);
    void mouse_callback(GLFWwindow * window, double xpos, double ypos);
};

class Core
{
public:
    
    void begin(void);
    
    void end(void);
    
    void update(void);
    
    void render(void);
    
    void clearScreen(void);
    
    void updateScreen(void);
    
    Core() {}
    ~Core() {}
    
    Vertex getVertexOfIndex(GLuint index) { return this->vertices[index]; }
    
    
private:
    
    friend class InputHandler;
    
    InputHandler * inputHandler;
    
    std::vector<Vertex> vertices;    
};

Core::begin(void) {
    

#endif
