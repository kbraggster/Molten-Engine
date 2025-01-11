#include "MetalDevice.h"

MetalDevice::MetalDevice()
{
    m_Device = MTL::CreateSystemDefaultDevice();
    if (!m_Device)
    {
        MLTN_CORE_INFO("[METAL] Failed to create Metal device!");
        return;
    }

    MLTN_CORE_INFO("[METAL] Device created: {0}", m_Device->name()->utf8String());

    // Create the command queue
    m_CommandQueue = m_Device->newCommandQueue();
    if (!m_CommandQueue)
    {
        MLTN_CORE_ERROR("[METAL] Failed to create command queue!");
        return;
    }

    MLTN_CORE_INFO("[METAL] Command queue created");
}

MetalDevice::~MetalDevice()
{
}