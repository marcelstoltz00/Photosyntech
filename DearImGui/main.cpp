#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector>

static void glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

int main() {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        return -1;
    }

    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac

    GLFWwindow* window = glfwCreateWindow(800, 600, "Dear ImGui Basic Example", nullptr, nullptr);
    if (window == nullptr) {
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Application state
    char input_buffer[256] = "";
    std::vector<std::string> text_entries;
    bool show_demo_window = false;
    float slider_value = 0.5f;
    ImVec4 color_picker = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    int counter = 0;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Main application window
        ImGui::Begin("Dear ImGui Basic Demo");

        ImGui::Text("Welcome to Dear ImGui!");
        ImGui::Separator();

        // Text input section
        ImGui::Text("Text Input:");
        ImGui::InputText("##input", input_buffer, sizeof(input_buffer));
        ImGui::SameLine();
        if (ImGui::Button("Add Text") || ImGui::IsKeyPressed(ImGuiKey_Enter)) {
            if (strlen(input_buffer) > 0) {
                text_entries.push_back(std::string(input_buffer));
                memset(input_buffer, 0, sizeof(input_buffer));
            }
        }
        ImGui::SameLine();
        if (ImGui::Button("Clear All")) {
            text_entries.clear();
        }

        ImGui::Separator();

        // Display text entries
        ImGui::Text("Text Entries (%zu items):", text_entries.size());
        ImGui::BeginChild("TextEntries", ImVec2(0, 150), true);
        for (size_t i = 0; i < text_entries.size(); i++) {
            ImGui::Text("%zu: %s", i + 1, text_entries[i].c_str());
        }
        ImGui::EndChild();

        ImGui::Separator();

        // Interactive controls
        ImGui::Text("Interactive Controls:");
        ImGui::SliderFloat("Slider", &slider_value, 0.0f, 1.0f);
        ImGui::ColorEdit3("Color Picker", (float*)&color_picker);

        if (ImGui::Button("Counter++")) {
            counter++;
        }
        ImGui::SameLine();
        ImGui::Text("Counter: %d", counter);

        ImGui::Separator();

        ImGui::Checkbox("Show Demo Window", &show_demo_window);
        if (show_demo_window) {
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                   1000.0f / io.Framerate, io.Framerate);

        ImGui::End();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
                    clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}