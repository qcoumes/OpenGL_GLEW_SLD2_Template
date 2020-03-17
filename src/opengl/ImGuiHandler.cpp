#include <opengl/ImGuiHandler.hpp>
#include <SDL_events.h>


namespace opengl {
    
    ImGuiHandler::ImGuiHandler(SDL_Window *window, SDL_GLContext context) :
            window(window) {
        
        #ifdef __APPLE__
        // GL 3.2 Core + GLSL 150
        const char* glsl_version = "#version 150";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        #else
        // GL 3.0 + GLSL 130
        const char *glsl_version = "#version 130";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        #endif
        
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        
        this->io = ImGui::GetIO();
        
        ImGui_ImplSDL2_InitForOpenGL(window, context);
        ImGui_ImplOpenGL3_Init(glsl_version);
    }
    
    
    void ImGuiHandler::newFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(this->window);
        ImGui::NewFrame();
    }
    
    
    void ImGuiHandler::handleEvent(const SDL_Event &event) {
        ImGui_ImplSDL2_ProcessEvent(&event);
    }
    
    
    void ImGuiHandler::render() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    
    
    bool ImGuiHandler::wantCaptureMouse() {
        return io.WantCaptureMouse;
    }
    
    
    bool ImGuiHandler::wantCaptureKeyboard() {
        return io.WantCaptureKeyboard;
    }
}

