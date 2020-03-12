#ifndef OPENGL_UNIFORMMATRIX34_HPP
#define OPENGL_UNIFORMMATRIX34_HPP

#include <opengl/shader/uniform/IUniform.hpp>


namespace opengl::shader {
    
    class UniformMatrix3x4fv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //OPENGL_UNIFORMMATRIX34_HPP
