#ifndef OPENGL_CONFIG_HPP
#define OPENGL_CONFIG_HPP

#include <string>

#include <GL/glew.h>
#include <glm/vec3.hpp>

#include <opengl/util/INonCopyable.hpp>
#include <opengl/Window.hpp>
#include <opengl/Camera.hpp>


namespace opengl {
    
    enum struct Framerate : GLbyte {
        FRAMERATE_60,
        FRAMERATE_75,
        FRAMERATE_120,
        FRAMERATE_144,
        FRAMERATE_180,
        FRAMERATE_240,
        FRAMERATE_VSYNC,
        FRAMERATE_UNCAPPED
    };
    
    
    
    class Config : public util::ISingleton {
        
        public:
            static constexpr GLuint TICK_PER_SEC = 60;
        
        private:
            std::string OpenGLVersion; /**< Version of OpenGL. */
            std::string GLEWVersion;   /**< Version of GLEW. */
            std::string CPUInfo;       /**< CPU brand and core information. */
            
            GLint width;  /**< Width of the window. */
            GLint height; /**< Height of the window. */
            
            GLfloat mouseSensitivity = 0.10f; /**< Sensitivity of the mouse, default to 0.5. */
            GLfloat fov = 70;      /**< Field of view, default to 70. */
            GLuint framerate = 0;  /**< Framerate value, default to 0 (uncapped). */
            GLuint usPerFrame = 0; /**< Number of microseconds between frame. */
            Framerate framerateOpt = Framerate::FRAMERATE_VSYNC;  /**< Chosen Framerate, default to VSYNC. */
            
            GLboolean faceCulling = true;      /**< Whether face culling is enabled. */
            GLboolean occlusionCulling = true; /**< Whether occlusion culling is enabled. */
            GLboolean frustumCulling = true;   /**< Whether frustum culling is enabled. */
            GLboolean debug = false;           /**< Whether debug display. */
            
            Config() = default;
        
        public:
            
            static Config *getInstance();
            
            void init(const Window &window, Camera &camera);
            
            void setOpenGlVersion(const std::string &openGlVersion);
            
            void setGlewVersion(const std::string &GlewVersion);
            
            void setCpuInfo(const std::string &cpuinfo);
            
            void setMouseSensitivity(GLfloat mouseSensitivity);
        
            void setWidth(GLint width);
        
            void setHeight(GLint height);
            
            void setFramerate(Framerate framerate, const Window &window);
            
            void cycleFramerate(const Window &window);
            
            void setFov(GLfloat fov, const Window &window, Camera &camera);
            
            void setFaceCulling(GLboolean faceCulling);
            
            void switchFaceCulling();
            
            void setOcclusionCulling(GLboolean occlusionCulling);
            
            void switchOcclusionCulling();
            
            void setFrustumCulling(GLboolean frustumCulling);
            
            void switchFrustumCulling();
            
            void setDebug(GLboolean debug);
            
            void switchDebug();
            
            [[nodiscard]] std::string getOpenGlVersion() const;
            
            [[nodiscard]] std::string getGlewVersion() const;
            
            [[nodiscard]] std::string getCpuInfo() const;
            
            [[nodiscard]] GLfloat getMouseSensitivity() const;
            
            [[nodiscard]] GLint getWidth() const;
            
            [[nodiscard]] GLint getHeight() const;
            
            [[nodiscard]] GLuint getFramerate() const;
            
            [[nodiscard]] GLuint getFramerateInv() const;
            
            [[nodiscard]] std::string getFramerateString() const;
            
            [[nodiscard]] GLfloat getFov() const;
            
            [[nodiscard]] GLboolean getFaceCulling() const;
            
            [[nodiscard]] GLboolean getOcclusionCulling() const;
            
            [[nodiscard]] GLboolean getFrustumCulling() const;
            
            [[nodiscard]] GLboolean getDebug() const;
    };
}

#endif // OPENGL_CONFIG_HPP
