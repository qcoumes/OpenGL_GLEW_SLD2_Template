#include <chrono>
#include <GL/glew.h>

#include <opengl/Engine.hpp>


using namespace opengl;


int main(int argc, char **argv) {
    Engine game = Engine();
    
    game.init();
    
    while (game.isRunning()) {
        
        if (game.tick()) {
            game.update();
        }
        
        game.render();
    }
    
    game.cleanup();
    
    return EXIT_SUCCESS;
}

