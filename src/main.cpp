#include <iostream>
#include <vulkan/vulkan.hpp>

int main()
{
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::cout << extensionCount << " extentions supported.\n";
    return 0;
}