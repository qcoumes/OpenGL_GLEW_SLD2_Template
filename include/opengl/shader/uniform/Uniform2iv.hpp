#ifndef OPENGL_UNIFORM2iv_HPP
#define OPENGL_UNIFORM2iv_HPP

#include <opengl/shader/uniform/IUniform.hpp>


namespace opengl::shader {
    
    class Uniform2iv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //OPENGL_UNIFORM2iv_HPP
