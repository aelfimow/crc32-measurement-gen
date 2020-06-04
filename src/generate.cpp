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
    r64 &tmp_reg;
};

static void gen_function(param_regs &pr, r64 &out_reg, size_t value)
{
    std::string const func_name { "crc32_8" };

    comment("uint32_t " + func_name + "(uint32_t crc_iv, const void *p_data, size_t count)");

    comment("crc_iv is in " + pr.crc_reg.name());
    comment("p_data is in " + pr.p_data_reg.name());
    comment("count is in " + pr.count_reg.name());
    comment("output crc is in " + out_reg.name());
    comment("temporary register is " + pr.tmp_reg.name());

    global(func_name);

    section code { ".text" };
    code.start();

    label(func_name);

    MOV(out_reg, pr.crc_reg);

    imm64 inc_value { value };
    MOV(pr.tmp_reg, inc_value);

    std::string func_start { func_name + "_start" };
    std::string func_end { func_name + "_end" };

    label(func_start);
    TEST(pr.count_reg, pr.count_reg);
    JZ(func_end);

    m8 buf_addr { pr.p_data_reg };

    CRC32(out_reg, buf_addr);
    ADD(pr.p_data_reg, pr.tmp_reg);
    DEC(pr.count_reg);
    JMP(func_start);

    label(func_end);
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
            RCX, RDX, R8, R9
        };

        r64 &out_reg { RAX };

        gen_function(windows_param_regs, out_reg, 1);
    }

    if (for_linux)
    {
        param_regs linux_param_regs
        {
            RDI, RSI, RDX, RCX
        };

        r64 &out_reg { RAX };

        gen_function(linux_param_regs, out_reg, 1);
    }

    return EXIT_SUCCESS;
}
catch (...)
{
    std::cerr << "Error, exception" << std::endl;

    return EXIT_FAILURE;
}
