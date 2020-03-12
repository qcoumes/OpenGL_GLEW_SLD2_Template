#include <opengl/shader/uniform/Uniform1uiv.hpp>


namespace opengl::shader {
    
    void Uniform1uiv::load(const void *value) {
        glUniform1uiv(this->location, 1, static_cast<const GLuint *>(value));
    }
}
