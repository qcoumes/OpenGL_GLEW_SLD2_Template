#ifndef OPENGL_STATS_HPP
#define OPENGL_STATS_HPP

#include <GL/glew.h>

#include <opengl/util/ISingleton.hpp>


namespace app {
    
    class Stats : public opengl::util::ISingleton {
        
        public:
            GLuint fps;
        
        private:
            
            Stats() = default;
        
        public:
            
            static Stats *getInstance();
    };
}

#endif // OPENGL_STATS_HPP
