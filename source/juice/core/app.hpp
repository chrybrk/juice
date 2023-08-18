#pragma once

#include "utils.hpp"
#include "timer.hpp"
#include "event/event.hpp"
#include "layer/layer_stack.hpp"

namespace juice {
    class Application
    {
    public:
        Application();
        virtual ~Application();
        
        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        void Run();

    public:

    private:
        static Application* s_Instance;
        // Timer m_Timer = Timer::GetInstance();
        LayerStack m_LayerStack;
    };
    
    Application* CreateApplication();
}
