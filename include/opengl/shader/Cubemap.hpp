#ifndef OPENGL_CUBEMAP_HPP
#define OPENGL_CUBEMAP_HPP

#include <memory>

#include <GL/glew.h>

#include <opengl/util/INonCopyable.hpp>
#include <opengl/util/Image.hpp>


namespace opengl::shader {
    
    class Cubemap : public util::INonCopyable {
        private:
            GLuint textureId = 0;
        
        public:
            
            Cubemap() = default;
            
            explicit Cubemap(std::unique_ptr<util::Image> texture[6]);
            
            [[nodiscard]] GLuint getCubemapId() const;
    };
}

#endif // OPENGL_CUBEMAP_HPP
