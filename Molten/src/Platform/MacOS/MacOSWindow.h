#pragma once

#include "Engine/Core/Window.h"

#include "Platform/Metal/MetalContext.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>

class MacOSWindow : public Window
{
  public:
    explicit MacOSWindow(const WindowProps& props);
    ~MacOSWindow() override;

    void OnUpdate() override;

    unsigned int GetWidth() const override { return m_Data.Width; }
    unsigned int GetHeight() const override { return m_Data.Height; }

    // Window attributes
    void SetVSync(bool enabled) override;
    bool IsVSync() const override;

    void* GetNativeWindow() const override { return m_Window; }

  private:
    virtual void Init(const WindowProps& props);
    virtual void Shutdown();

    GLFWwindow* m_Window;

    struct WindowData
    {
        std::string Title;
        unsigned int Width, Height;
        bool VSync;
    };

    WindowData m_Data;
    MetalContext m_Context;
    MTL::CommandQueue* m_CommandQueue;
    CA::MetalDrawable* m_Drawable;
};