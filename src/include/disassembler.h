#include <stdlib.h>

/*************************************
 * Structure representing an op code *
 ************************************/
struct instruction {
    const char* name; /**< name of operation, represented in op_code array */
    uint8_t     len;  /**< bytes of operation, represented in op_len array */
};

/**********************************************
 * Returns an instruction for the value given *
 *                                            *
 * @param value hex code to be decoded        *
 * @return instruction struct with 
 *********************************************/
struct instruction instruction_for_value(uint8_t);

/********************************
 * Operation codes for the 8080 *
 * @see op_len
 *******************************/
static const char* op_code[256] =
{
    "NOP\t", "LXI\tB ", "STAX\tB ", "INX\tB ", "INR\tB ", "DCR\tB ", "MVI\tB ",
    "RLC\t", " ", "DAD\tB ", "LDAX\tB ", "DCX\tB ", "INR\tC ", "DCR\tC ", "MVI\tC ",
    "RRC\t", " ", "LXI\tD ", "STAX\tD ", "INX\tD ", "INR\tD ", "DCR\tD ", "MVI\tD ",
    "RAL\t", " ", "DAD\tD ", "LDAX\tD ", "DCX\tD ", "INR\tE ", "DCR\tE ", "MVI\tE ",
    "RAR\t", "RIM\t", "LXI\tH ", "SHLD\t", "INX\tH ", "INR\tH ", "DCR\tH ",
    "MVI\tH ", "DAA\t", " ", "DAD\tH ", "LHLD\t", "DCX\tH ", "INR\tL ", "DCR\tL ",
    "MVI\tL ", "CMA\t", "SIM\t", "LXI\tSP ", "STA\t", "INX\tSP ", "INR\tM ",
    "DCR\tM ", "MVI\tM ", "STC\t", " ", "DAD\tSP ", "LDA\t", "DCX\tSP ", "INR\tA ",
    "DCR\tA ", "MVI\tA ", "CMC\t", "MOV\tB, B ", "MOV\tB, C ", "MOV\tB, D ",
    "MOV\tB, E ", "MOV\tB, H ", "MOV\tB, L ", "MOV\tB, M ", "MOV\tB, A ",
    "MOV\tC, B ", "MOV\tC, C ", "MOV\tC, D ", "MOV\tC, E ", "MOV\tC, H ",
    "MOV\tC, L ", "MOV\tC, M ", "MOV\tC, A ", "MOV\tD, B ", "MOV\tD, C ",
    "MOV\tD, D ", "MOV\tD, E ", "MOV\tD, H ", "MOV\tD, L ", "MOV\tD, M ",
    "MOV\tD, A ", "MOV\tE, B ", "MOV\tE, C ", "MOV\tE, D ", "MOV\tE, E ",
    "MOV\tE, H ", "MOV\tE, L ", "MOV\tE, M ", "MOV\tE, A ", "MOV\tH, B ",
    "MOV\tH, C ", "MOV\tH, D ", "MOV\tH, E ", "MOV\tH, H ", "MOV\tH, L ",
    "MOV\tH, M ", "MOV\tH, A ", "MOV\tL, B ", "MOV\tL, C ", "MOV\tL, D ",
    "MOV\tL, E ", "MOV\tL, H ", "MOV\tL, L ", "MOV\tL, M ", "MOV\tL, A ",
    "MOV\tM, B ", "MOV\tM, C ", "MOV\tM, D ", "MOV\tM, E ", "MOV\tM, H ",
    "MOV\tM, L ", "HLT\t", "MOV\tM, A ", "MOV\tA, B ", "MOV\tA, C ", "MOV\tA, D ",
    "MOV\tA, E ", "MOV\tA, H ", "MOV\tA, L ", "MOV\tA, M ", "MOV\tA, A ", "ADD\tB ",
    "ADD\tC ", "ADD\tD ", "ADD\tE ", "ADD\tH ", "ADD\tL ", "ADD\tM ", "ADD\tA ",
    "ADC\tB ", "ADC\tC ", "ADC\tD ", "ADC\tE ", "ADC\tH ", "ADC\tL ", "ADC\tM ",
    "ADC\tA ", "SUB\tB ", "SUB\tC ", "SUB\tD ", "SUB\tE ", "SUB\tH ", "SUB\tL ",
    "SUB\tM ", "SUB\tA ", "SBB\tB ", "SBB\tC ", "SBB\tD ", "SBB\tE ", "SBB\tH ",
    "SBB\tL ", "SBB\tM ", "SBB\tA ", "ANA\tB ", "ANA\tC ", "ANA\tD ", "ANA\tE ",
    "ANA\tH ", "ANA\tL ", "ANA\tM ", "ANA\tA ", "XRA\tB ", "XRA\tC ", "XRA\tD ",
    "XRA\tE ", "XRA\tH ", "XRA\tL ", "XRA\tM ", "XRA\tA ", "ORA\tB ", "ORA\tC ",
    "ORA\tD ", "ORA\tE ", "ORA\tH ", "ORA\tL ", "ORA\tM ", "ORA\tA ", "CMP\tB ",
    "CMP\tC ", "CMP\tD ", "CMP\tE ", "CMP\tH ", "CMP\tL ", "CMP\tM ", "CMP\tA ",
    "RNZ\t", "POP\tB ", "JNZ\t", "JMP\t", "CNZ\t", "PUSH\tB ", "ADI\t", "RST\t0 ",
    "RZ\t", "RET\t", "JZ\t", " ", "CZ\t", "CALL\t", "ACI\t", "RST\t1 ", "RNC\t",
    "POP\tD ", "JNC\t", "OUT\t", "CNC\t", "PUSH\tD ", "SUI\t", "RST\t2 ", "RC\t",
    " ", "JC\t", "IN\t", "CC\t", " ", "SBI\t", "RST\t3 ", "RPO\t", "POP\tH ",
    "JPO\t", "XTHL\t", "CPO\t", "PUSH\tH ", "ANI\t", "RST\t4 ", "RPE\t",
    "PCHL\t", "JPE\t", "XCHG\t", "CPE\t", " ", "XRI\t", "RST\t5 ", "RP ",
    "POP\tPSW ", "JP\t", "DI\t", "CP\t", "PUSH\tPSW ", "ORI\t", "RST\t6 ", "RM\t",
    "SPHL\t", "JM\t", "EI\t", "CM\t", " ", "CPI\t", "RST\t7"
};

/**
 * Lengths for operation codes for 8080
 * @see op_code[]
 */
static const uint8_t op_len[256] =
{
    1, 3, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
    1, 3, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
    1, 3, 3, 1, 1, 1, 2, 1, 1, 1, 3, 1, 1, 1, 2, 1,
    1, 3, 3, 1, 1, 1, 2, 1, 1, 1, 3, 1, 1, 1, 2, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 3, 3, 3, 1, 2, 1, 1, 1, 3, 3, 3, 3, 2, 1,
    1, 1, 3, 2, 3, 1, 2, 1, 1, 1, 3, 2, 3, 3, 2, 1,
    1, 1, 3, 1, 3, 1, 2, 1, 1, 1, 3, 1, 3, 3, 2, 1,
    1, 1, 3, 1, 3, 1, 2, 1, 1, 1, 3, 1, 3, 3, 2, 1
};
