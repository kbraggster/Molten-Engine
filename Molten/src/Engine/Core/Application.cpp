#include "Application.h"

Application* Application::s_Instance = nullptr;

Application::Application()
{
    s_Instance = this;

    m_Window.reset(Window::Create());
}

void Application::Run()
{
    while (m_Running)
    {
        m_Window->OnUpdate();
    }
}

Application* CreateApplication()
{
    return new Application();
}
