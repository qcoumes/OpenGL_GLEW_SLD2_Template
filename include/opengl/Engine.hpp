#ifndef OPENGL_ENGINE_HPP
#define OPENGL_ENGINE_HPP

#include <cstdint>
#include <chrono>
#include <memory>

#include <GL/glew.h>

#include <opengl/Window.hpp>
#include <opengl/Camera.hpp>
#include <opengl/Input.hpp>


namespace opengl {
    
    class Engine {
        private:
            static constexpr GLuint64 TICK_PER_SEC = 60;
            static constexpr GLdouble MS_PER_TICK = 1. / TICK_PER_SEC * 1000.;
        
        private:
            std::unique_ptr<Window> window = nullptr;
            std::unique_ptr<Camera> camera = nullptr;
            std::unique_ptr<Input> input = nullptr;
            
            std::chrono::steady_clock::time_point lastTick;
            GLboolean running = true;
            GLuint tickSecond = 0;
            GLuint tickCount = 0;
        
            void debug(GLuint fps) const;
        
            void _render() const;
        
        public:
        
            Engine() = default;
        
            void init();
        
            GLboolean tick();
        
            void update();
        
            void render() const;
        
            void cleanup();
            
            [[nodiscard]] GLboolean isRunning();
    };
}

#endif // OPENGL_ENGINE_HPP
