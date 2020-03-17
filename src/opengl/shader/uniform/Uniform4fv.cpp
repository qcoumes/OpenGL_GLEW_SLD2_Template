#include <opengl/shader/uniform/Uniform4fv.hpp>


namespace opengl::shader {
    
    void Uniform4fv::load(const void *value) {
        glUniform4fv(this->location, 1, static_cast<const GLfloat *>(value));
    }
}
