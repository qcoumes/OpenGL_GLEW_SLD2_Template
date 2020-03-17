#include <chrono>
#include <iostream>
#include <iomanip>
#include <memory>

#include <imgui/imgui.h>

#include <app/Engine.hpp>
#include <app/Config.hpp>
#include <app/Stats.hpp>
#include <opengl/ImGuiHandler.hpp>


namespace app {
    
    Engine *Engine::getInstance() {
        static Engine engine;
        return &engine;
    }
    
    
    void Engine::init() {
        this->window = std::make_unique<opengl::Window>("OpenGL");
        
        GLenum glewInitError = glewInit();
        if (GLEW_OK != glewInitError) {
            throw std::runtime_error(reinterpret_cast<const char *>(glewGetErrorString(glewInitError)));
        }
        
        this->lastTick = std::chrono::steady_clock::now();
        this->camera = std::make_unique<opengl::Camera>();
        this->input = std::make_unique<opengl::Input>();
        this->imGui = std::make_unique<opengl::ImGuiHandler>(this->window->getWindow(), this->window->getContext());
        Config::getInstance()->init(*this->window, *this->camera);
        
        glEnable(GL_BLEND);
        glEnable(GL_CULL_FACE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    
    
    GLboolean Engine::tick() {
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        double duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->lastTick).count();
        
        if (duration >= MS_PER_TICK) {
            this->lastTick = now;
            this->tickCount++;
            this->tickSecond = (this->tickSecond + 1) % TICK_PER_SEC;
            return true;
        }
        
        return false;
    }
    
    
    void Engine::update() {
        Config *config = Config::getInstance();
        GLfloat speed = config->getSpeed();
        SDL_Event event;
        
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEMOTION:
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEWHEEL:
                    if (this->imGui->wantCaptureMouse()) {
                        this->imGui->handleEvent(event);
                    }
                    else {
                        this->input->handleInput(event);
                    }
                    break;
                
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    if (this->imGui->wantCaptureKeyboard()) {
                        this->imGui->handleEvent(event);
                    }
                    else {
                        this->input->handleInput(event);
                    }
                    break;
                
                default:
                    this->input->handleInput(event);
            }
        }
        
        // Close app
        if (this->input->ended() || this->input->isReleasedKey(SDL_SCANCODE_ESCAPE)) {
            this->running = false;
        }
        
        // Movements
        if (this->input->isHeldKey(SDL_SCANCODE_A)) {
            this->camera->moveLeft(speed);
        }
        if (this->input->isHeldKey(SDL_SCANCODE_D)) {
            this->camera->moveLeft(speed);
        }
        if (this->input->isHeldKey(SDL_SCANCODE_W)) {
            this->camera->moveForward(speed);
        }
        if (this->input->isHeldKey(SDL_SCANCODE_S)) {
            this->camera->moveForward(speed);
        }
        if (this->input->isHeldKey(SDL_SCANCODE_SPACE)) {
            this->camera->moveUp(speed);
        }
        if (this->input->isHeldKey(SDL_SCANCODE_LCTRL)) {
            this->camera->moveUp(speed);
        }
        
        // Toggle debug
        if (this->input->isReleasedKey(SDL_SCANCODE_F10)) {
            config->switchDebug();
        }
    }
    
    
    void Engine::debug() const {
        Config *config = Config::getInstance();
        Engine *engine = Engine::getInstance();
        glm::dvec3 position = engine->camera->getPosition();
        std::stringstream ss;
        GLint length;
        
        this->imGui->newFrame();
        ImGui::SetNextWindowSize({ 600, 300 }, ImGuiCond_FirstUseEver);
        ImGui::Begin("Debug");
        ImGui::Text("FPS: %d /", Stats::getInstance()->fps);
        ImGui::SameLine();
        ImGui::PushItemWidth(105);
        if (ImGui::BeginCombo("", config->getFramerateString().c_str())) {
            for (GLint i = 0; i <= Framerate::FRAMERATE_LAST; i++) {
                bool is_selected = (config->getFramerateOpt() == i);
                if (ImGui::Selectable(config->getFramerateString(i).c_str(), is_selected)) {
                    config->setFramerate(static_cast<Framerate>(i));
                }
                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        length = static_cast<GLint>(std::to_string(Config::TICK_PER_SEC).size());
        ss.str(std::string());
        ss << "Tick: " << std::setfill('0') << std::setw(length) << engine->tickSecond << "/" << Config::TICK_PER_SEC;
        ImGui::Text("%s", ss.str().c_str());
        ImGui::Text("Position: (%.2f, %.2f, %.2f)", position.x, position.y, position.z);
        ImGui::Dummy({ 0.0f, 6.0f });
        
        if (ImGui::CollapsingHeader("Hardware & Driver")) {
            GLint offset = 120;
            ImGui::Text("CPU:");
            ImGui::SameLine(offset);
            ImGui::Text("%s", config->getCpuInfo().c_str());
            
            ImGui::Text("OpenGL Version:");
            ImGui::SameLine(offset);
            ImGui::Text("%s", config->getOpenGlVersion().c_str());
            
            ImGui::Text("GLEW Version:");
            ImGui::SameLine(offset);
            ImGui::Text("%s", config->getGlewVersion().c_str());
        }
        
        if (ImGui::CollapsingHeader("Settings")) {
            bool faceCulling = config->getFaceCulling();
            ImGui::Checkbox("Face Culling", &faceCulling);
            if (faceCulling != config->getFaceCulling()) {
                config->switchFaceCulling();
            }
        }
        
        ImGui::End();
        this->imGui->render();
    }
    
    
    void Engine::_render() const {
        //        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
    
    void Engine::render() const {
        static std::chrono::steady_clock::time_point cmptStart = std::chrono::steady_clock::now();
        static std::chrono::steady_clock::time_point limiterStart = cmptStart;
        static GLuint fps = 0;
        
        std::chrono::steady_clock::time_point now;
        double duration;
        
        if (Config::getInstance()->getFramerate() > 0) { // Capped framerate
            now = std::chrono::steady_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(now - limiterStart).count();
            if (duration >= Config::getInstance()->getFramerateInv()) {
                this->_render();
                if (Config::getInstance()->getDebug()) {
                    this->debug();
                }
                this->window->refresh();
                limiterStart = now;
                fps++;
            }
        }
        else { // Uncapped framerate
            this->_render();
            if (Config::getInstance()->getDebug()) {
                this->debug();
            }
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
