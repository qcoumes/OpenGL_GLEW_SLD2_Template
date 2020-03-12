#ifndef OPENGL_UNIFORMMAXTRIX3_HPP
#define OPENGL_UNIFORMMAXTRIX3_HPP

#include <opengl/shader/uniform/IUniform.hpp>


namespace opengl::shader {
    
    class UniformMatrix3fv : public IUniform {
        
        public:
        
            using IUniform::IUniform;
            
            void load(const void *value) final;
    };
}

#endif //OPENGL_UNIFORMMAXTRIX3_HPP
