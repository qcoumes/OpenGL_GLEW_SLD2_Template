#ifndef OPENGL_ENGINE_HPP
#define OPENGL_ENGINE_HPP

#include <cstdint>
#include <chrono>
#include <memory>

#include <GL/glew.h>

#include <opengl/Window.hpp>
#include <opengl/Camera.hpp>
#include <opengl/Input.hpp>
#include <opengl/ImGuiHandler.hpp>


namespace app {
    
    class Engine : public opengl::util::ISingleton {
        private:
            static constexpr GLuint64 TICK_PER_SEC = 60;
            static constexpr GLdouble MS_PER_TICK = 1. / TICK_PER_SEC * 1000.;
        
        private:
            std::unique_ptr<opengl::ImGuiHandler> imGui = nullptr;
            std::unique_ptr<opengl::Window> window = nullptr;
            std::unique_ptr<opengl::Camera> camera = nullptr;
            std::unique_ptr<opengl::Input> input = nullptr;
            
            std::chrono::steady_clock::time_point lastTick;
            GLboolean running = true;
            GLuint tickSecond = 0;
            GLuint tickCount = 0;
        
            void debug() const;
        
            void _render() const;
        
            Engine() = default;
            
        public:
        
            static Engine *getInstance();
        
            void init();
        
            GLboolean tick();
        
            void update();
        
            void render() const;
        
            void cleanup();
            
            [[nodiscard]] GLboolean isRunning();
    };
}

#endif // OPENGL_ENGINE_HPP
