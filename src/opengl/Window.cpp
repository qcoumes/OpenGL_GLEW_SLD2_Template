#include <iostream>

#include <SDL.h>

#include <opengl/Window.hpp>
#include <opengl/Config.hpp>


namespace opengl {
    
    Window::Window(const char *title, uint32_t flags) {
        if (0 != SDL_Init(SDL_INIT_VIDEO)) {
            throw std::runtime_error(SDL_GetError());
        }
        
        this->window = SDL_CreateWindow(
                title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0,
                SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP | flags
        );
        if (this->window == nullptr) {
            throw std::runtime_error(SDL_GetError());
        }
        
        this->context = SDL_GL_CreateContext(this->window);
        if (this->context == nullptr) {
            throw std::runtime_error(SDL_GetError());
        }
    }
    
    Window::Window(const char *title, int32_t width, int32_t height, uint32_t flags) {
        if (0 != SDL_Init(SDL_INIT_VIDEO)) {
            throw std::runtime_error(SDL_GetError());
        }
        
        this->window = SDL_CreateWindow(
                title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
                SDL_WINDOW_OPENGL | flags
        );
        if (this->window == nullptr) {
            throw std::runtime_error(SDL_GetError());
        }
        
        this->context = SDL_GL_CreateContext(this->window);
        if (this->context == nullptr) {
            throw std::runtime_error(SDL_GetError());
        }
    }
    
    
    Window::~Window() {
        SDL_GL_DeleteContext(this->context);
        SDL_DestroyWindow(this->window);
    }
    
    
    void Window::handleWindowEvent(const SDL_WindowEvent &event, Camera &camera) {
        if (event.windowID != SDL_GetWindowID(this->window)) {
            return;
        }
        
        switch (event.type) {
            case SDL_WINDOWEVENT_RESIZED:
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                camera.setProjectionMatrix(Config::getInstance()->getFov(), event.data1, event.data2);
                break;
            
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                SDL_SetRelativeMouseMode(SDL_TRUE);
                break;
            
            case SDL_WINDOWEVENT_FOCUS_LOST:
                SDL_SetRelativeMouseMode(SDL_FALSE);
                break;
        }
    }
    
    
    void Window::refresh() {
        SDL_GL_SwapWindow(this->window);
    }
    
    
    SDL_DisplayMode Window::getDisplayMode() const {
        SDL_DisplayMode mode;
        
        if (SDL_GetDesktopDisplayMode(0, &mode)) {
            throw std::runtime_error(SDL_GetError());
        }
        
        return mode;
    }
}
