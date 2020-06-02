#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <sstream>

#include "cppasm.h"

int main(int argc, char *argv[])
try
{
    const std::string usageStr { "Usage: generate windows|linux" };

    if (argc != 2)
    {
        throw std::invalid_argument(usageStr);
    }

    std::string os { argv[1] };

    bool for_windows { os == "windows" };
    bool for_linux { os == "linux" };

    if (!for_windows && !for_linux)
    {
        throw std::invalid_argument(usageStr);
    }

    if (for_windows)
    {
        // TODO
    }

    if (for_linux)
    {
        // TODO
    }

    return EXIT_SUCCESS;
}
catch (...)
{
    std::cerr << "Error, exception" << std::endl;

    return EXIT_FAILURE;
}
