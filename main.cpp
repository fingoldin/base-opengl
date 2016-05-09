#include "core.h"

Core core;

int main(int argc, char ** argv)
{
    core.begin();
    
    while(!core.shouldClose())
    {
        core.update();
        
        core.clearScreen();
        
        core.render();
        
        core.updateScreen();
    }
    
    core.end();
    
    return 0;
}
