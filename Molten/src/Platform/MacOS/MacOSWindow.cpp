#include "MacOSWindow.h"

#include "spdlog/fmt/bundled/color.h"

#include <AppKit/AppKit.hpp>
#include <Platform/Metal/Adapters/GLFWAdapter.h>

static bool s_GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char* description)
{
    MLTN_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

Window* Window::Create(const WindowProps& props)
{
    return new MacOSWindow(props);
}

MacOSWindow::MacOSWindow(const WindowProps& props)
{
    MacOSWindow::Init(props);
}

MacOSWindow::~MacOSWindow()
{
    MacOSWindow::Shutdown();
}

void MacOSWindow::Init(const WindowProps& props)
{
    m_Data.Title  = props.Title;
    m_Data.Width  = props.Width;
    m_Data.Height = props.Height;

    MLTN_CORE_INFO("Creating Window: {0} ({1}, {2})", props.Title, props.Width, props.Height);

    if (!s_GLFWInitialized)
    {
        // TODO: glfwTerminate on system shutdown
        int success = glfwInit();
        MLTN_CORE_ASSERT(success, "Could not initialize GLFW!");
        glfwSetErrorCallback(GLFWErrorCallback);

        s_GLFWInitialized = true;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    m_Window = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), m_Data.Title.c_str(),
                                nullptr, nullptr);

    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);

    // Set GLFW callbacks
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        data.Width  = width;
        data.Height = height;
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
    });

    m_Context.Init();

    NS::Window* nsWindow = GetNSWindow(m_Window, m_Context.GetMetalLayer())->retain();
    m_CommandQueue       = m_Context.GetDevice()->newCommandQueue();
}

void MacOSWindow::Shutdown()
{
    glfwDestroyWindow(m_Window);
}

void MacOSWindow::OnUpdate()
{
    glfwPollEvents();

    // Get the next drawable from the Metal layer
    m_Drawable = m_Context.GetMetalLayer()->nextDrawable();

    if (!m_Drawable)
        MLTN_CORE_ERROR("Drawable is null!");

    // Create a command buffer
    MTL::CommandBuffer* commandBuffer = m_CommandQueue->commandBuffer();

    // Set up render pass descriptor
    MTL::RenderPassDescriptor* renderPass                     = MTL::RenderPassDescriptor::alloc()->init();
    MTL::RenderPassColorAttachmentDescriptor* colorAttachment = renderPass->colorAttachments()->object(0);
    colorAttachment->setTexture(m_Drawable->texture());
    colorAttachment->setLoadAction(MTL::LoadActionClear);
    colorAttachment->setClearColor(MTL::ClearColor(0.7f, 0.2f, 0.2f, 1.0f));
    colorAttachment->setStoreAction(MTL::StoreActionStore);

    // Begin encoding commands for rendering
    MTL::RenderCommandEncoder* renderCommandEncoder = commandBuffer->renderCommandEncoder(renderPass);
    renderCommandEncoder->endEncoding(); // No actual drawing, just clearing the color

    // Present the drawable and commit the command buffer
    commandBuffer->presentDrawable(m_Drawable);
    commandBuffer->commit();
    commandBuffer->waitUntilCompleted();
}

void MacOSWindow::SetVSync(const bool enabled)
{
    m_Data.VSync = enabled;
}

bool MacOSWindow::IsVSync() const
{
    return m_Data.VSync;
}