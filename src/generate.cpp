#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <sstream>

#include "cppasm.h"

struct param_regs
{
    r64 &crc_reg;
    r64 &p_data_reg;
    r64 &count_reg;
};

static void gen_function(param_regs &pr, r64 &out_reg)
{
    std::string const func_name { "crc32_8" };

    comment("uint32_t " + func_name + "(uint32_t crc, const void *p_data, size_t count)");

    comment("crc is in " + pr.crc_reg.name());
    comment("p_data is in " + pr.p_data_reg.name());
    comment("count is in " + pr.count_reg.name());

    global(func_name);

    section code { ".text" };
    code.start();

    label(func_name);

    m8 buf_addr { pr.p_data_reg };

    CRC32(out_reg, buf_addr);

    RET();
}

int main(int argc, char *argv[])
try
{
    std::string const usageStr { "Usage: generate windows|linux" };

    if (argc != 2)
    {
        throw std::invalid_argument(usageStr);
    }

    std::string const os { argv[1] };

    bool const for_windows { os == "windows" };
    bool const for_linux { os == "linux" };

    if (!for_windows && !for_linux)
    {
        throw std::invalid_argument(usageStr);
    }

    if (for_windows)
    {
        param_regs windows_param_regs
        {
            RCX, RDX, R8
        };

        r64 &out_reg { RAX };

        gen_function(windows_param_regs, out_reg);
    }

    if (for_linux)
    {
        param_regs linux_param_regs
        {
            RDI, RSI, RDX
        };

        r64 &out_reg { RAX };

        gen_function(linux_param_regs, out_reg);
    }

    return EXIT_SUCCESS;
}
catch (...)
{
    std::cerr << "Error, exception" << std::endl;

    return EXIT_FAILURE;
}
