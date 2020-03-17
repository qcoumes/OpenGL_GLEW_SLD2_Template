#include <opengl/shader/uniform/Uniform2uiv.hpp>


namespace opengl::shader {
    
    void Uniform2uiv::load(const void *value) {
        glUniform2uiv(this->location, 1, static_cast<const GLuint *>(value));
    }
}
