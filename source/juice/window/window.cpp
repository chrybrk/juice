#include "pch.hpp"

#include "window.hpp"
#include "core/utils.hpp"
#include "event/app_event.hpp"
#include "event/key_event.hpp"
#include "event/mouse_event.hpp"

namespace juice {

    static bool isGLFWWindowCreated = false;

    GLFWwindow *Window::m_Window = nullptr;
    Window::WindowData Window::m_WindowData;

    void Window::Init(const WindowProps& props)
    {
        m_WindowData.Title = props.title;
        m_WindowData.Width = props.width;
        m_WindowData.Height = props.height;
        m_WindowData.Alive = true;

        if (!isGLFWWindowCreated)
        {
            int glfwIniti = glfwInit();
            isGLFWWindowCreated = true;
            ASSERT(glfwIniti, "GLFW Failed to Init!");
        }

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // properties
        glfwWindowHint(GLFW_RESIZABLE, props.resizable);

        m_Window = glfwCreateWindow((int)m_WindowData.Width, (int)m_WindowData.Height, m_WindowData.Title.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(m_Window, &m_WindowData);

        glfwMakeContextCurrent(m_Window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        ASSERT(status, "GLAD Failed to Init!");

        glViewport(0, 0, (int)m_WindowData.Width, (int)m_WindowData.Height);

        // Set Vsync true (cap at 60 fps)
        SetVSync(true);

        //////////////////////////////////////////////
        //				Window Event 				//
        //////////////////////////////////////////////

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Alive = false;
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            glViewport(0, 0, (int)width, (int)height);

            WindowSizeEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int xpos, int ypos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowPosEvent event(xpos, ypos);
            data.EventCallback(event);
        });

        glfwSetWindowRefreshCallback(m_Window, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowRefreshEvent event;
            data.EventCallback(event);
        });

        glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowFocusedEvent event(focused);
            data.EventCallback(event);
        });

        //////////////////////////////////////////////
        //				Keyboard Event 				//
        //////////////////////////////////////////////

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
            }
        });


        //////////////////////////////////////////////
        //				Mouse Event 				//
        //////////////////////////////////////////////

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MousePositionEvent event((float)xpos, (float)ypos);
            data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseScrollEvent event((float)xoffset, (float)yoffset);
            data.EventCallback(event);
        });
    }

    void Window::Terminate() 
    {
        glfwDestroyWindow(m_Window);
        // glfwTerminate();
    }

    void Window::OnClear()
    {
        glClearColor(m_WindowData.color.r, m_WindowData.color.g, m_WindowData.color.b, m_WindowData.color.a);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    }

    void Window::OnUpdate() 
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void Window::SetVSync(bool enabled)
    {
        if(enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_WindowData.VSync = enabled;
    }
}
