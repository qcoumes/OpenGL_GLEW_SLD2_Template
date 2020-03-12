#include <opengl/shader/uniform/Uniform2iv.hpp>


namespace opengl::shader {
    
    void Uniform2iv::load(const void *value) {
        glUniform2iv(this->location, 1, static_cast<const GLint *>(value));
    }
}
