#ifndef OPENGL_UNIFORM4uiv_HPP
#define OPENGL_UNIFORM4uiv_HPP

#include <opengl/shader/uniform/IUniform.hpp>


namespace opengl::shader {
    
    class Uniform4uiv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //OPENGL_UNIFORM4uiv_HPP
