#include <opengl/shader/uniform/Uniform3iv.hpp>


namespace opengl::shader {
    
    void Uniform3iv::load(const void *value) {
        glUniform3iv(this->location, 1, static_cast<const GLint *>(value));
    }
}
