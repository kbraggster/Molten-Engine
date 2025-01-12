#include "MetalDevice.h"

MetalDevice::MetalDevice()
{
    m_Device = MTL::CreateSystemDefaultDevice();
    if (!m_Device)
    {
        MLTN_CORE_ERROR("[METAL] Failed to create Metal device!");
        return;
    }

    MLTN_CORE_INFO("[METAL] Device created: {0}", m_Device->name()->utf8String());
}

MetalDevice::~MetalDevice()
{
    m_Device->release();
}