#import "GLFWAdapter.h"

NS::Window* GetNSWindow(GLFWwindow* glfwWindow, CA::MetalLayer* layer) {
    CALayer* obj_layer = (__bridge CALayer*) layer;
    NSWindow* obj_window = glfwGetCocoaWindow(glfwWindow);

    obj_window.contentView.layer = obj_layer;
    obj_window.contentView.wantsLayer = YES;

    return (__bridge NS::Window*)obj_window;
}