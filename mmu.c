#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "mmu.h"
#include "cart.h"

static uint8_t wram[0x2000];   // 8KiB Work Ram
static uint8_t vram[0x2000];   // 8KiB Video Ram
static uint8_t xram[0x2000];   // 8KiB Cartridge/External Ram
static uint8_t hram[0x127];    // High-Ram (127 bytes)
static uint8_t oam[0xA0];      // Object-Attribute Memory (160 bytes)
static uint8_t *rom;           // ROM

uint8_t read8(uint16_t addr) {
    switch(addr) {
        case 0x0000 ... 0x3FFF: // 16 KiB ROM bank 00
            return rom[addr];
        case 0x4000 ... 0x7FFF: // 16 KiB ROM bank 01-NN
            // TODO: Implement  
            return 0; 
        case 0x8000 ... 0x9FFF: // 8  KiB VRAM
            return vram[addr - 0x8000];
        case 0xA000 ... 0xBFFF: // 8  KiB Cartridge RAM
            // TODO: Implement  
            return 0; 
        case 0xC000 ... 0xCFFF: // 4  KiB WRAM 
            return wram[addr - 0xC000];
        case 0xD000 ... 0xDFFF: // 4  KiB WRAM (CGB mode: bank 1-7)
            return wram[addr - 0xC000];
        case 0xE000 ... 0xFDFF: // Echo RAM, Mirror of C000-DDFF
            return wram[addr - 0xE000];
        case 0xFE00 ... 0xFE9F: // Object-Attribute memory (OAM)
            // TODO: Implement lock on this later
            return oam[addr - 0xFE00];
        case 0xFEA0 ... 0xFEFF: // Not Usable
            // TODO: Return $FF when OAM is blocked (add check), otherwise 
            //       return 0
            return 0;
        case 0xFF00 ... 0xFF7F: // I/O Registers
            // TODO: Implement  
            
            return 0; 
        case 0xFF80 ... 0xFFFE: // High RAM
            return hram[addr - 0xFF80];
        case 0xFFFF:            // Interrupt Enable register (IE)
            // TODO: Implement  
            return 0; 
        default:
            return 0;
    }
}

void write8(uint16_t addr, uint8_t val) {
    switch(addr) {
        case 0x0000 ... 0x3FFF: // 16 KiB ROM bank 00
            // TODO: Implement MBC handler
            return;
        case 0x4000 ... 0x7FFF: // 16 KiB ROM bank 01-NN
            // TODO: Implement switchable bank / mapper
            return; 
        case 0x8000 ... 0x9FFF: // 8  KiB VRAM
            vram[addr - 0x800] = val;
            return;
        case 0xA000 ... 0xBFFF: // 8  KiB Cartridge RAM
            xram[addr - 0xA000]= val;
            return; 
        case 0xC000 ... 0xCFFF: // 4  KiB WRAM
            wram[addr - 0XC000] = val;
            return;
        case 0xD000 ... 0xDFFF: // 4  KiB WRAM (CGB mode: bank 1-7)
            // TODO: Add check for CGB mode later
            wram[addr - 0xD000] = val;
            return;
        case 0xE000 ... 0xFDFF: // Echo RAM, Mirror of C000-DDFF 
            wram[addr - 0xE000] = val;
            return;
        case 0xFE00 ... 0xFE9F: // Object attribute memory (OAM)
            // TODO: Implement  
            oam[addr - 0xFE00] = val;
            return;
        case 0xFEA0 ... 0xFEFF: // Not Usable
            return; 
        case 0xFF00 ... 0xFF7F: // I/O Registers
            // TODO: Implement  
            return; 
        case 0xFF80 ... 0xFFFE: // High RAM
            hram[addr - 0xFF80] = val;
            return;
        case 0xFFFF:            // Interrupt Enable register (IE)
            // TODO: Implement  
            return; 
        default:
            return;
    }
}

void mmu_load_rom(const char *path) {

    // Opens rom file, gets file size in bytes
    FILE *f = fopen(path, "rb");
    fseek(f, 0, SEEK_END);
    size_t file_size = ftell(f);
    rewind(f);

    // Loads rom data into memory, closes file
    rom = malloc(file_size);
    fread(rom, 1, file_size, f);
    fclose(f);

    // Prints title bytes 
    printf("Title:\t\t");
    for (int i = 0x0134; i <= 0x0143; i++) {
        if (rom[i] == '\0') break;
        printf("%c", rom[i]);
    }
    printf("\n");

    // Decodes and prints cartridge type
    printf("Cartridge Type:\t%s\n", get_cart_type(rom[0x0147]));

    // Decodes and prints ROM size
    printf("Rom Size:\t%u KB\n", get_rom_size(rom[0x0148]) / 1024);

    // Prints checksum value
    printf("Checksum Val:\t0x%02X\n", rom[0x014D]);

}