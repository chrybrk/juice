#include "pch.hpp"
#include "app.hpp"

#include "window/window.hpp"

namespace juice {

    Application::Application()
    {
        Window::Init();
        Window::SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if(e.Handled())
                break;
        }
    }

    void Application::PushLayer(Layer* layer) 
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay) 
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    void Application::Run()
    {
        timer.Init();
    	while(Window::IsAlive())
        {
            Window::OnClear();

            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate(timer.DeltaTime());
            }

            Window::OnUpdate();

            timer.Tick();
        }
    }

    Application::~Application()
    {
    	Window::Terminate();
    }

}
