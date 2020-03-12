#ifndef OPENGL_UNIFORM1uiv_HPP
#define OPENGL_UNIFORM1uiv_HPP

#include <opengl/shader/uniform/IUniform.hpp>


namespace opengl::shader {
    
    class Uniform1uiv : public IUniform {
        
        public:
            
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //OPENGL_UNIFORM1uiv_HPP
