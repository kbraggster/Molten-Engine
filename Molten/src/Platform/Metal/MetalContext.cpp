#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include "MetalContext.h"

void MetalContext::Init()
{
    m_Device = std::make_unique<MetalDevice>();
}