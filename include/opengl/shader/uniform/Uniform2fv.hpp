#ifndef OPENGL_UNIFORM2FV_HPP
#define OPENGL_UNIFORM2FV_HPP

#include <opengl/shader/uniform/IUniform.hpp>


namespace opengl::shader {
    
    class Uniform2fv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //OPENGL_UNIFORM2FV_HPP
