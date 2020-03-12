#include <chrono>
#include <memory>

#include <opengl/Engine.hpp>
#include <opengl/Config.hpp>
#include <opengl/Stats.hpp>
#include <iostream>
#include <imgui/imgui.h>
#include <sstream>


namespace opengl {
    
    void Engine::init() {
        this->window = std::make_unique<Window>("OpenGL");
        
        GLenum glewInitError = glewInit();
        if (GLEW_OK != glewInitError) {
            throw std::runtime_error(reinterpret_cast<const char *>(glewGetErrorString(glewInitError)));
        }
        
        this->lastTick = std::chrono::steady_clock::now();
        
        this->camera = std::make_unique<Camera>();
        this->input = std::make_unique<Input>();
        
        Config::getInstance()->init(*this->window, *this->camera);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    
    
    GLboolean Engine::tick() {
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        double duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->lastTick).count();
        
        if (duration >= MS_PER_TICK) {
            this->tickCount++;
            this->tickSecond = (this->tickSecond + 1) % TICK_PER_SEC;
            return true;
        }
        
        return false;
    }
    
    
    void Engine::update() {
        this->input->handleInput();
        
        if (this->input->ended() || this->input->isReleasedKey(SDL_SCANCODE_ESCAPE)) {
            this->running = false;
        }
        
        if (this->input->isReleasedKey(SDL_SCANCODE_F10)) {
            Config::getInstance()->switchDebug();
        }
    }
    
    
    void Engine::debug(GLuint fps) const {
        std::stringstream ss;
        
        ImGui::Begin("Debug");
        
        ss.str(std::string());
        ss << "FPS: " << fps << "/" << Config::getInstance()->getFramerateString();
        ImGui::Text("%s", ss.str().c_str());
        
        ImGui::End();
    }
    
    
    void Engine::_render() const {
    }
    
    
    void Engine::render() const {
        static std::chrono::steady_clock::time_point cmptStart = std::chrono::steady_clock::now();
        static std::chrono::steady_clock::time_point limiterStart = cmptStart, now;
        static double duration;
        static GLuint fps = 0;
        
        if (Config::getInstance()->getFramerate() > 0) { // Capped framerate
            now = std::chrono::steady_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(now - limiterStart).count();
            if (duration >= Config::getInstance()->getFramerateInv()) {
                if (Config::getInstance()->getDebug()) {
                    this->debug(fps);
                }
                this->_render();
                this->window->refresh();
                fps++;
            }
        }
        else { // Uncapped framerate
            if (Config::getInstance()->getDebug()) {
                this->debug(fps);
            }
            this->_render();
            this->window->refresh();
            fps++;
        }
        
        // Computing FPS
        now = std::chrono::steady_clock::now();
        duration = std::chrono::duration_cast<std::chrono::seconds>(now - cmptStart).count();
        if (duration >= 1.) {
            Stats::getInstance()->fps = static_cast<GLuint>(fps);
            fps = 0;
            cmptStart = now;
        }
    }
    
    
    void Engine::cleanup() {
    }
    
    
    GLboolean Engine::isRunning() {
        return this->running;
    }
}
