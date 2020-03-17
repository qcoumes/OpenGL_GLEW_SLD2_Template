#include <opengl/shader/uniform/UniformMatrix2x4fv.hpp>


namespace opengl::shader {
    
    void UniformMatrix2x4fv::load(const void *value) {
        glUniformMatrix2x4fv(this->location, 1, GL_FALSE, static_cast<const GLfloat *>(value));
    }
}
