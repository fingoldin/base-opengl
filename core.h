#ifndef CORE_H
#define CORE_H

#include <cstdlib>
#include <cstdio>

#include <string>
#include <vector>
#include <cmath>

#ifndef GLEW_STATIC
    #define GLEW_STATIC
#endif
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transformation.hpp>

#include "mesh.h"

struct Vertex {
    glm::vec3 Position;
    
    glm::vec3 Normal;
    
    glm::vec2 UV;
    
    GLuint Texture;
};


class Core
{
public:
    
    void begin(const char * winName);
    
    void end(void);
    
    bool shouldClose(void);
    
    void update(void);
    
    void render(void);
    
    void clearScreen(void)
    
    void updateScreen(void);
    
    Core() {}
    ~Core() {}  
    
private:
    
    void init_gl(void);
    void setup_meshes(void);
    
    void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);
    void scroll_callback(GLFWwindow * window, double xoffset, double yoffset);
    void mouse_callback(GLFWwindow * window, double xpos, double ypos);
    
    friend class Shader;
    Shader * shader;
    
    bool keys[1024];
    
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
    
    std::string vertex_shader_path;
    std::string fragment_shader_path;
    
    GLFWmonitor * window_monitor;
    GLFWwindow * window_share;
    GLFWwindow * window;
    
    GLfloat ltime;
    
    glm::mat4 model_mat;
    glm::mat4 view_mat;
    glm::mat4 projection_mat;
    
    glm::vec3 cam_position;
    glm::vec3 cam_target;
    glm::vec3 cam_up;
};

void Core::begin(const char * winName)
{
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
    
    this->vertex_shader_path = "shader.vs";
    this->fragment_shader_path = "shader.frag";
    
    this->window_monitor = NULL;
    this->window_share = NULL;
    this->window = NULL;
    
    this->ltime = 0;
    
    this->model_mat = glm::mat4(1.0f);
    this->view_mat = glm::mat4(1.0f);
    this->projection_mat = glm::mat4(1.0f);
    
    this->cam_position = glm::vec3(0.0f, 0.0f, 1.0f);
    this->cam_target = glm::vec3(0.0f, 0.0f, 0.0f);
    this->cam_up = glm::vec3(0.0f, 1.0f, 0.0f);
    
    this->init_gl();
}

void Core::end(void)
{
    glfwTerminate();
    
    delete this->shader;
}

bool Core::shouldClose()
{
    if(glfwWindowShouldClose(this->window))
        return true;
    else
        return false;
}

void Core::update()
{
    GLfloat ctime = glfwGetTime();
    GLfloat dtime = ctime - ltime;
    ltime = ctime;
    
    glfwPollEvents();
    
    this->shader->Use();
    
    this->model_mat = glm::mat4(1.0f);
    this->view_mat = glm::lookAt(this->cam_position, this->cam_target, this->cam_up);
    this->projection_mat = glm::perspective(glm::radians(45.0f), this->window_width / this->window_height, 0.1f, 100.0f);
    
    glUniformMatrix4fv(glGetUniformLocation(this->shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(this->model_mat));
    glUniformMatrix4fv(glGetUniformLocation(this->shader->Program, "view"), 1, GL_FALSE, glm::value_ptr(this->view_mat));
    glUniformMatrix4fv(glGetUniformLocation(this->shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(this->projection_mat));
}

void Core::render()
{
    for(int i = 0; i < this->meshes.size(); i++)
        this->meshes[i].render();
}

void Core::clearScreen(void)
{
    glClearColor(this->clear_color[0], this->clear_color[1], this->clear_color[2], this->clear_color[3]);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
}

void Core::updateScreen(void)
{
    glfwSwapBuffers();
}

void Core::init_gl(void)
{
    if(glfwInit() != GL_TRUE) {
        std::printf("\nERROR in Core::init_gl(void): could not initialize GLFW!\nTerminating program...\n");
        std::exit(1);
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
    
    glfwSetKeyCallback(window, this->key_callback);
    glfwSetCursorPosCallback(window, this->mouse_callback);
    glfwSetScrollCallback(window, this->scroll_callback);
    
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        std::printf("\nERROR in Core::init_gl(void): could not initialize GLEW!\nTerminating program...\n");
        std::exit(1);
    }
    
    glViewport(this->viewport_x, this->viewport_y, this->viewport_w, this->viewport_h);
    
    glEnable(GL_DEPTH_TEST);
    
    this->shader = new Shader(this->vertex_shader_path.c_str(), this->fragment_shader_path.c_str());
}

void Core::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(this->window, GL_TRUE);

    if(action == GLFW_PRESS)
        this->keys[key] = true;
    else if(action == GLFW_RELEASE)
        this->keys[key] = false;	
}

void scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{

}

void mouse_callback(GLFWwindow * window, double xpos, double ypos)
{

}

#endif
