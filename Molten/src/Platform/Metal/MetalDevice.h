#pragma once

#include <Metal/Metal.hpp>

class MetalDevice
{
  public:
    MetalDevice();
    ~MetalDevice();

    MTL::Device* GetDevice() const { return m_Device; }

  private:
    MTL::Device* m_Device             = nullptr;
    MTL::CommandQueue* m_CommandQueue = nullptr;
};