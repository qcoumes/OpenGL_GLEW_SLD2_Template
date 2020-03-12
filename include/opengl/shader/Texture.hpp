#ifndef OPENGL_TEXTURE_HPP
#define OPENGL_TEXTURE_HPP

#include <memory>

#include <GL/glew.h>

#include <opengl/util/INonCopyable.hpp>
#include <opengl/util/Image.hpp>


namespace opengl::shader {
    
    class Texture  {
        private:
            GLuint textureId = 0;
        
        public:
            
            Texture() = default;
            
            explicit Texture(const util::Image *texture);
            
            explicit Texture(GLuint textureId);
        
            void bind() const;
            
            void unbind() const;
    };
}

#endif //OPENGL_TEXTURE_HPP
