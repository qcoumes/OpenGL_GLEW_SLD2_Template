#include <sstream>
#include <iostream>

#include <SDL_mouse.h>
#include <cpuid/libcpuid.h>

#include <opengl/Config.hpp>


namespace opengl {
    
    Config *Config::getInstance() {
        static Config config;
        return &config;
    }
    
    
    void Config::init(const Window &window, Camera &camera) {
        this->setOpenGlVersion(reinterpret_cast<const char *>(glGetString(GL_VERSION)));
        this->setGlewVersion(reinterpret_cast<const char *>(glewGetString(GLEW_VERSION)));
        this->setFramerate(Framerate::FRAMERATE_VSYNC, window);
        this->setFov(70, window, camera);
        this->setFaceCulling(true);
        
        SDL_DisplayMode display = window.getDisplayMode();
        this->width = display.w;
        this->height = display.h;
        SDL_SetRelativeMouseMode(SDL_TRUE);
        
        struct cpu_raw_data_t raw {};
        struct cpu_id_t data {};
        if (cpuid_get_raw_data(&raw) < 0 || cpu_identify(&raw, &data) < 0) {
            this->CPUInfo = "Unknown";
        }
        else {
            std::stringstream ss;
            ss << data.brand_str << " - " << data.num_cores << " cores (" << data.num_logical_cpus << " threads)";
            this->CPUInfo = ss.str();
        }
    }
    
    
    std::string Config::getOpenGlVersion() const {
        return this->OpenGLVersion;
    }
    
    
    void Config::setOpenGlVersion(const std::string &openGlVersion) {
        this->OpenGLVersion = openGlVersion;
    }
    
    
    std::string Config::getGlewVersion() const {
        return this->GLEWVersion;
    }
    
    
    void Config::setGlewVersion(const std::string &glewVersion) {
        this->GLEWVersion = glewVersion;
    }
    
    
    std::string Config::getCpuInfo() const {
        return this->CPUInfo;
    }
    
    
    void Config::setCpuInfo(const std::string &cpuInfo) {
        this->CPUInfo = cpuInfo;
    }
    
    
    GLfloat Config::getMouseSensitivity() const {
        return mouseSensitivity;
    }
    
    
    void Config::setMouseSensitivity(GLfloat mouseSensitivity) {
        this->mouseSensitivity = mouseSensitivity;
    }
    
    
    void Config::setWidth(GLint width) {
        this->width = width;
    }
    
    
    void Config::setHeight(GLint height) {
        this->height = height;
    }
    
    
    GLint Config::getWidth() const {
        return this->width;
    }
    
    
    GLint Config::getHeight() const {
        return this->height;
    }
    
    
    GLuint Config::getFramerate() const {
        return framerate;
    }
    
    
    GLuint Config::getFramerateInv() const {
        return usPerFrame;
    }
    
    
    std::string Config::getFramerateString() const {
        switch (this->framerateOpt) {
            case Framerate::FRAMERATE_60:
                return "60";
            case Framerate::FRAMERATE_75:
                return "75";
            case Framerate::FRAMERATE_120:
                return "120";
            case Framerate::FRAMERATE_144:
                return "144";
            case Framerate::FRAMERATE_180:
                return "180";
            case Framerate::FRAMERATE_240:
                return "240";
            case Framerate::FRAMERATE_VSYNC:
                return std::to_string(this->framerate) + " (VSYNC)";
            case Framerate::FRAMERATE_UNCAPPED:
                return "Uncapped";
        }
    }
    
    
    void Config::setFramerate(Framerate framerate, const Window &window) {
        GLuint fps;
        
        this->framerateOpt = framerate;
        
        switch (framerate) {
            case Framerate::FRAMERATE_60:
                this->framerate = 60;
                this->usPerFrame = static_cast<GLuint>(1. / 60. * 1e6);
                break;
            case Framerate::FRAMERATE_75:
                this->framerate = 75;
                this->usPerFrame = static_cast<GLuint>(1. / 75. * 1e6);
                break;
            case Framerate::FRAMERATE_120:
                this->framerate = 120;
                this->usPerFrame = static_cast<GLuint>(1. / 120. * 1e6);
                break;
            case Framerate::FRAMERATE_144:
                this->framerate = 144;
                this->usPerFrame = static_cast<GLuint>(1. / 144. * 1e6);
                break;
            case Framerate::FRAMERATE_180:
                this->framerate = 180;
                this->usPerFrame = static_cast<GLuint>(1. / 180. * 1e6);
                break;
            case Framerate::FRAMERATE_240:
                this->framerate = 240;
                this->usPerFrame = static_cast<GLuint>(1. / 240. * 1e6);
                break;
            case Framerate::FRAMERATE_VSYNC:
                fps = static_cast<GLuint>(window.getDisplayMode().refresh_rate);
                this->framerate = fps ? fps : 60;
                this->usPerFrame = static_cast<GLuint>(1. / this->framerate * 1e6);
                break;
            case Framerate::FRAMERATE_UNCAPPED:
                this->framerate = 0;
                this->usPerFrame = 0;
                break;
        }
    }
    
    
    void Config::cycleFramerate(const Window &window) {
        switch (this->framerateOpt) {
            case Framerate::FRAMERATE_60:
                this->setFramerate(Framerate::FRAMERATE_75, window);
                break;
            case Framerate::FRAMERATE_75:
                this->setFramerate(Framerate::FRAMERATE_120, window);
                break;
            case Framerate::FRAMERATE_120:
                this->setFramerate(Framerate::FRAMERATE_144, window);
                break;
            case Framerate::FRAMERATE_144:
                this->setFramerate(Framerate::FRAMERATE_180, window);
                break;
            case Framerate::FRAMERATE_180:
                this->setFramerate(Framerate::FRAMERATE_240, window);
                break;
            case Framerate::FRAMERATE_240:
                this->setFramerate(Framerate::FRAMERATE_VSYNC, window);
                break;
            case Framerate::FRAMERATE_VSYNC:
                this->setFramerate(Framerate::FRAMERATE_UNCAPPED, window);
                break;
            case Framerate::FRAMERATE_UNCAPPED:
                this->setFramerate(Framerate::FRAMERATE_60, window);
                break;
        }
    }
    
    
    GLfloat Config::getFov() const {
        return fov;
    }
    
    
    void Config::setFov(GLfloat fov, const Window &window, Camera &camera) {
        this->fov = fov;
        SDL_DisplayMode display = window.getDisplayMode();
        camera.setProjectionMatrix(fov, display.w, display.h);
    }
    
    
    GLboolean Config::getFaceCulling() const {
        return faceCulling;
    }
    
    
    void Config::setFaceCulling(GLboolean faceCulling) {
        this->faceCulling = faceCulling;
    }
    
    
    void Config::switchFaceCulling() {
        this->faceCulling = !this->faceCulling;
    }
    
    
    GLboolean Config::getOcclusionCulling() const {
        return occlusionCulling;
    }
    
    
    void Config::setOcclusionCulling(GLboolean occlusionCulling) {
        this->occlusionCulling = occlusionCulling;
    }
    
    
    void Config::switchOcclusionCulling() {
        this->occlusionCulling = !this->occlusionCulling;
    }
    
    
    GLboolean Config::getFrustumCulling() const {
        return frustumCulling;
    }
    
    
    void Config::setFrustumCulling(GLboolean frustumCulling) {
        this->frustumCulling = frustumCulling;
    }
    
    
    void Config::switchFrustumCulling() {
        this->frustumCulling = !this->frustumCulling;
    }
    
    
    GLboolean Config::getDebug() const {
        return debug;
    }
    
    
    void Config::setDebug(GLboolean debug) {
        this->debug = debug;
    }
    
    
    void Config::switchDebug() {
        this->debug = !this->debug;
    }
}
