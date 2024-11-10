#include "lve_pipeline.h"

// C++ includes
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace lve
{

LvePipeline::LvePipeline(std::string const& vertFilepath, std::string const& fragFilepath)
{
    // Instantiating
    CreateGraphicsPipeline(vertFilepath, fragFilepath);
}

std::vector<char> LvePipeline::ReadFile(std::string const& filepath)
{
    // Opening file and seeking to end and reading in binary
    std::ifstream file{filepath, std::ios::ate | std::ios::binary};

    // Making sure file opens
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filepath);
    }

    // Getting file since tellg is already at end1
    size_t fileSize = static_cast<size_t>(file.tellg());

    // Character buffer for reading
    std::vector<char> buffer(fileSize);

    // Reading
    file.seekg(0);
    file.read(buffer.data(), fileSize);

    // Closing
    file.close();
    return buffer;
}

void LvePipeline::CreateGraphicsPipeline(std::string const& vertFilepath, std::string const& fragFilepath)
{
    // Grabbing shader files
    auto vertCode = ReadFile(vertFilepath);
    auto fragCode = ReadFile(fragFilepath);

    // Outputting shader file size for confirmation
    std::cout << "Vertex Shader code size: " << vertCode.size() << '\n';
    std::cout << "Fragment Shader code size: " << fragCode.size() << '\n';
}

}  // namespace lve
