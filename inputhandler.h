#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

class InputHandler
{
public:
    
    static void begin(GLFWwindow * window);
    
    static void end();
    
    static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);
    static void scroll_callback(GLFWwindow * window, double xoffset, double yoffset);
    static void mouse_callback(GLFWwindow * window, double xpos, double ypos);
    
    static void update(GLfloat dtime);
    
private:
    
    InputHandler() { }
    
    static bool keys[1024];
    
};

#endif
