#ifndef OPENGL_UNIFORMMATRIX32_HPP
#define OPENGL_UNIFORMMATRIX32_HPP

#include <opengl/shader/uniform/IUniform.hpp>


namespace opengl::shader {
    
    class UniformMatrix3x2fv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //OPENGL_UNIFORMMATRIX32_HPP
