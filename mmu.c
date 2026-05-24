#include <stdint.h>

static uint8_t wram[0x2000];   // 8KiB Work Ram
static uint8_t vram[0x2000];   // 8KiB Video Ram

uint8_t read8(uint16_t addr) {

    // 1. Find where the address falls acording to memory map
    switch(addr) {
        case 0x0000 ... 0x3FFF: // 16 KiB ROM bank 00
        case 0x4000 ... 0x7FFF: // 16 KiB ROM bank 01-NN
        case 0x8000 ... 0x9FFF: // 8  KiB VRAM
        case 0xA000 ... 0xBFFF: // 8  KiB Cartridge RAM
        case 0xC000 ... 0xCFFF: // 4  KiB WRAM 
        case 0xD000 ... 0xDFFF: // 4  KiB WRAM (CGB mode: bank 1-7)
        case 0xE000 ... 0xFDFF: // Echo RAM, Mirror of C000-DDFF
        case 0xFE00 ... 0xFE9F: // Object attribute memory (OAM)
        case 0xFEA0 ... 0xFEFF: // Not Usable
        case 0xFF00 ... 0xFF7F: // I/O Registers
        case 0xFF80 ... 0xFFFE: // High RAM
        case 0xFFFF:            // Interrupt Enable register (IE)


    }
    // 2. Grab the byte at the correct location

}