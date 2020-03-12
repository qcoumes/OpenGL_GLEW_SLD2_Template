#ifndef OPENGL_WINDOW_HPP
#define OPENGL_WINDOW_HPP

#include <SDL_video.h>
#include <SDL_events.h>

#include <opengl/Camera.hpp>
#include <opengl/util/ISingleton.hpp>


namespace opengl {
    
    class Window : public util::INonCopyable {
        private:
            SDL_Window *window;
            SDL_GLContext context;
        
        public:
            
            explicit Window(const char *title, uint32_t flags = 0);
            
            explicit Window(const char *title, int32_t width, int32_t height, uint32_t flags = 0);
            
            ~Window();
            
            void handleWindowEvent(const SDL_WindowEvent &event, Camera &camera);
            
            void refresh();
            
            [[nodiscard]] SDL_DisplayMode getDisplayMode() const;
    };
}

#endif //OPENGL_WINDOW_HPP
