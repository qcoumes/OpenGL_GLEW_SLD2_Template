#ifndef OPENGL_UNIFORMMATRIX24_HPP
#define OPENGL_UNIFORMMATRIX24_HPP

#include <opengl/shader/uniform/IUniform.hpp>


namespace opengl::shader {
    
    class UniformMatrix2x4fv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //OPENGL_UNIFORMMATRIX24_HPP
