#include <stdint.h>

uint8_t wram[0x2000];   // 8KiB Work Ram
uint8_t vram[0x2000];   // 8KiB Video Ram

uint8_t read8(uint16_t addr) {

    // 1. Find where the address falls acording to memory map
    // 2. Grab the byte at the correct location

}