#include "disassembler.h"

instruction_t instruction_for_value(uint8_t value)
{
    return (instruction_t){ op_code[value], op_len[value] };
}
