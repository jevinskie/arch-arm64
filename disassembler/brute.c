#include <stdint.h>

#include <arch-arm64/arm64dis.h>

int main(void) {
    for (uint64_t instr64 = 0; instr64 <= UINT32_MAX; ++instr64) {
        uint32_t instr = (uint32_t)instr64;
        Instruction inst_repr;
        if (aarch64_decompose(instr, &inst_repr, 0) != DECODE_STATUS_OK) {
            continue;
        }
    }
    return 0;
}
