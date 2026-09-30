#include <vulkan-triangle/util.hpp>
#include <fstream>

conduit::vector<char> vtapp::util::readFile(const conduit::string &fileSource)
{
    std::ifstream file(fileSource, std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
        throw std::runtime_error("failed to open file: " + fileSource);
    }

    // Allocate enough space for buffer.
    conduit::vector<char> buffer(file.tellg());
    
    // Read file from beginning.
    file.seekg(0, std::ios::beg);
    // Store data in buffer.
    file.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));

    // Close file.
    file.close();

    // Return buffer.
    return buffer;
}