#ifndef UTILS_H
#define UTILS_H

struct Vertex {
    glm::vec3 Position;
    
    glm::vec3 Normal;
    
    glm::vec2 UV;
    
    GLuint MaterialIndex;
};

struct Texture {
    std::string Path;
    
    GLuint ID;
};

struct Material {
    glm::vec3 Ambient;
    glm::vec3 Diffuse;
    
    Texture Tex;
};

#endif
