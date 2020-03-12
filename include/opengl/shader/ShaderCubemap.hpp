#ifndef OPENGL_SHADERCUBEMAP_HPP
#define OPENGL_SHADERCUBEMAP_HPP

#include <opengl/shader/Shader.hpp>
#include <opengl/shader/Cubemap.hpp>


namespace opengl::shader {
    
    class ShaderCubemap : public Shader {
        private:
            GLint uTexture = -1;
        
        public:
            
            ShaderCubemap() = default;
            
            ShaderCubemap(const std::string &vsFile, const std::string &fsFile);
            
            void bindCubemap(const Cubemap &texture) const;
            
            void unbindCubemap() const;
    };
}

#endif // OPENGL_SHADERCUBEMAP_HPP

