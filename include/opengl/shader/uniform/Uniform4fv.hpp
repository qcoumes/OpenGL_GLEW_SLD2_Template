#ifndef OPENGL_UNIFORM4FV_HPP
#define OPENGL_UNIFORM4FV_HPP

#include <opengl/shader/uniform/IUniform.hpp>


namespace opengl::shader {
    
    class Uniform4fv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //OPENGL_UNIFORM4FV_HPP
