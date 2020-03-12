#include <opengl/ImGuiHandler.hpp>


namespace opengl {
    
    void ImGuiHandler::start(SDL_Window *window) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();
    }
    
    
    void ImGuiHandler::render() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}

