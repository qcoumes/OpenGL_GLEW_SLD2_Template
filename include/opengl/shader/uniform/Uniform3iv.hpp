#ifndef OPENGL_UNIFORM3iv_HPP
#define OPENGL_UNIFORM3iv_HPP

#include <opengl/shader/uniform/IUniform.hpp>


namespace opengl::shader {
    
    class Uniform3iv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //OPENGL_UNIFORM3iv_HPP
