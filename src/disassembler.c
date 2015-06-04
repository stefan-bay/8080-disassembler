#include "include/disassembler.h"

struct instruction instruction_for_value(uint8_t value)
{
	return (struct instruction){ op_code[value], op_len[value] };
}
