#pragma once

#include <Metal/Metal.hpp>

#include "Engine/Renderer/GraphicsContext.h"

class MetalContext : public GraphicsContext
{
  public:
    MetalContext()           = default;
    ~MetalContext() override = default;

    void Init() override;

  private:
    MTL::Device* m_Device             = nullptr;
    MTL::CommandQueue* m_CommandQueue = nullptr;
};
