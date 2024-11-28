// Including our custom headers
#include "first_app.h"

// C++ includes
#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main()
{
    lve::FirstApp app{};

    try
    {
        app.Run();
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}