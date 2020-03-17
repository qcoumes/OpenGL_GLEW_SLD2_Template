#include <opengl/shader/uniform/Uniform3uiv.hpp>


namespace opengl::shader {
    
    void Uniform3uiv::load(const void *value) {
        glUniform3uiv(this->location, 1, static_cast<const GLuint *>(value));
    }
}
