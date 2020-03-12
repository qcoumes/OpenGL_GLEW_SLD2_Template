#ifndef OPENGL_UNIFORM1FV_HPP
#define OPENGL_UNIFORM1FV_HPP

#include <opengl/shader/uniform/IUniform.hpp>


namespace opengl::shader {
    
    class Uniform1fv : public IUniform {
        
        public:
            
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //OPENGL_UNIFORM1FV_HPP
