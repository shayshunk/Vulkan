#pragma once

// C++ includes
#include <string>
#include <vector>

namespace lve
{
class LvePipeline
{
  public:
    LvePipeline(std::string const& vertFilepath, std::string const& fragFilepath);

  private:
    static std::vector<char> ReadFile(std::string const& filepath);

    void CreateGraphicsPipeline(std::string const& vertFilepath, std::string const& fragFilepath);
};
}  // namespace lve