#ifndef OPENGL_STATS_HPP
#define OPENGL_STATS_HPP

#include <GL/glew.h>

#include <opengl/util/ISingleton.hpp>


namespace opengl {
    
    class Stats : public util::ISingleton {
        
        public:
            GLuint fps;
        
        private:
            
            Stats() = default;
        
        public:
            
            static Stats *getInstance();
    };
}

#endif // OPENGL_STATS_HPP
