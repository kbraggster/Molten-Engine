#pragma once

#include "MetalDevice.h"

#include "Engine/Renderer/GraphicsContext.h"

#include <QuartzCore/QuartzCore.hpp>

class MetalContext : public GraphicsContext
{
  public:
    MetalContext() = default;
    ~MetalContext() override;

    void Init() override;

    CA::MetalLayer* GetMetalLayer() const { return m_MetalLayer; }
    MTL::Device* GetDevice() const { return m_Device->GetDevice(); }

  private:
    std::unique_ptr<MetalDevice> m_Device;
    CA::MetalLayer* m_MetalLayer = nullptr;
};
