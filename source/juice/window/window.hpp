#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "core/utils.hpp"
#include "event/event.hpp"

namespace juice
{
    struct WindowProps
    {
        std::string title;
        std::uint32_t width;
        std::uint32_t height;
        bool resizable;

        WindowProps(const std::string& title = "juice engine",
                    std::uint32_t width = 800,
                    std::uint32_t height = 600,
                    bool resizable = false)
            : title(title), width(width), height(height), resizable(resizable)
        {  }
    };

    class Window
    {
        public:
            using EventCallbackFn = std::function<void(Event&)>;

            static void Init(const WindowProps& props = WindowProps());
            static void Terminate();

            static void OnClear();
            static void OnUpdate();
            static void SetVSync(bool enabled);

            static inline void SetEventCallback(const EventCallbackFn& callback) { m_WindowData.EventCallback = callback; };
            static inline void SetClearColor(glm::vec4 color) { m_WindowData.color = color; }
            static inline bool IsAlive() { return m_WindowData.Alive; }

            static void* GetNativeWindow() { return m_Window; }
            static glm::vec2 GetWindowSize() { return glm::vec2(m_WindowData.Width, m_WindowData.Height); }
            static std::uint32_t GetWidth() { return m_WindowData.Width; }
            static std::uint32_t GetHeight() { return m_WindowData.Height; }
        private:
            struct WindowData
            {
                std::string Title;
                std::uint32_t Width;
                std::uint32_t Height;

                glm::vec4 color;

                bool Alive;
                bool VSync;

                EventCallbackFn EventCallback;
            };

        private:
            static GLFWwindow* m_Window;
            static WindowData m_WindowData;
    };
}
