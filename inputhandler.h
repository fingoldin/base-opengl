#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

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

#endif
