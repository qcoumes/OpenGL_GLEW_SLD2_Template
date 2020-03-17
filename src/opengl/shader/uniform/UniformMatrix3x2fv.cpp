#include <opengl/shader/uniform/UniformMatrix3x2fv.hpp>


namespace opengl::shader {
    
    void UniformMatrix3x2fv::load(const void *value) {
        glUniformMatrix3x2fv(this->location, 1, GL_FALSE, static_cast<const GLfloat *>(value));
    }
}
