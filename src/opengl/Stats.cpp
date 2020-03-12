#include <opengl/Stats.hpp>


namespace opengl {
    
    Stats *opengl::Stats::getInstance() {
        static Stats stats;
        return &stats;
    }
}
