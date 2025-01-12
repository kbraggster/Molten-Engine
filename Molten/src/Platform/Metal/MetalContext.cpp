#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include "MetalContext.h"

#include <AppKit/AppKit.hpp>

MetalContext::~MetalContext()
{
    m_MetalLayer->release();
}

void MetalContext::Init()
{
    m_Device = std::make_unique<MetalDevice>();

    m_MetalLayer = CA::MetalLayer::layer()->retain();
    m_MetalLayer->setDevice(m_Device->GetDevice());
    m_MetalLayer->setPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm);
    m_MetalLayer->setFramebufferOnly(false);
    m_MetalLayer->setDrawableSize(CGSizeMake(1280, 720));
}