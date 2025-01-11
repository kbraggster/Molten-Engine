#pragma once

#include "MetalDevice.h"

#include "Engine/Renderer/GraphicsContext.h"


class MetalContext : public GraphicsContext
{
  public:
    MetalContext()           = default;
    ~MetalContext() override = default;

    void Init() override;

  private:
    std::unique_ptr<MetalDevice> m_Device;
};
