#ifndef OPENGL_IMGUIHANDLER_HPP
#define OPENGL_IMGUIHANDLER_HPP

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>

namespace opengl {
    
    class ImGuiHandler {
            
            static void start(SDL_Window *window);
            
            static void render();
    };
}

#endif //OPENGL_IMGUIHANDLER_HPP
