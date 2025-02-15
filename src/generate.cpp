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

template
<
    typename T1,
    typename T2
>
void gen_function
(
    std::string const &func_name,
    param_regs &pr,
    r64 &out_reg_full,
    T2 &out_reg_working,
    size_t value
)
{
    comment("uint32_t " + func_name + "(uint32_t crc_iv, const void *p_data, size_t count)");

    comment("crc_iv is in " + pr.crc_reg.name());
    comment("p_data is in " + pr.p_data_reg.name());
    comment("count is in " + pr.count_reg.name());
    comment("output crc is in " + out_reg_full.name());
    comment("temporary register is " + pr.tmp_reg.name());

    global(func_name);

    section code { ".text" };
    code.start();

    label(func_name);

    MOV(out_reg_full, pr.crc_reg);

    imm64 inc_value { value };
    MOV(pr.tmp_reg, inc_value);

    std::string func_start { func_name + "_start" };
    std::string func_end { func_name + "_end" };

    label(func_start);
    TEST(pr.count_reg, pr.count_reg);
    JZ(func_end);

    T1 buf_addr { pr.p_data_reg };

    CRC32(out_reg_working, buf_addr);
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

        gen_function<m8, r32>("crc32_8", windows_param_regs, RAX, EAX, 1);
        gen_function<m16, r32>("crc32_16", windows_param_regs, RAX, EAX, 2);
        gen_function<m32, r32>("crc32_32", windows_param_regs, RAX, EAX, 4);
        gen_function<m64, r64>("crc32_64", windows_param_regs, RAX, RAX, 8);
    }

    if (for_linux)
    {
        param_regs linux_param_regs
        {
            RDI, RSI, RDX, RCX
        };

        gen_function<m8, r32>("crc32_8", linux_param_regs, RAX, EAX, 1);
        gen_function<m16>("crc32_16", linux_param_regs, RAX, EAX, 2);
        gen_function<m32>("crc32_32", linux_param_regs, RAX, EAX, 4);
        gen_function<m64>("crc32_64", linux_param_regs, RAX, RAX, 8);
    }

    return EXIT_SUCCESS;
}
catch (...)
{
    std::cerr << "Error, exception" << std::endl;

    return EXIT_FAILURE;
}
