#include <stdint.h>

#define FLAG_Z 0x80  // bit 7
#define FLAG_N 0x40  // bit 6
#define FLAG_H 0x20  // bit 5
#define FLAG_C 0x10  // bit 4

typedef struct {

    uint8_t a, b, c, d, e, h, l, f;
    uint16_t sp, pc;
    uint64_t clock;

} CPU;

CPU cpu_init() {

    // Initializes to post-boot state (DMG)
    CPU cpu = {0};
    cpu.a = 0x01;
    cpu.b = 0x00;
    cpu.c = 0x13;
    cpu.d = 0x00;
    cpu.e = 0xD8;
    cpu.h = 0x01;
    cpu.l = 0x4D;

    // Set flags
    cpu.f |= FLAG_Z;
    cpu.f &= ~FLAG_N;
    // TODO: Calculate checksum and conditionally set H and C flags

    // Set PC, SP
    cpu.pc = 0x0100;
    cpu.sp = 0xFFFE;

    return cpu;

}