#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include "MetalContext.h"

void MetalContext::Init()
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