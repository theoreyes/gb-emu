#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

const char *get_cart_type(uint8_t type);
uint32_t get_rom_size(uint8_t val);

int main (int argc, char **argv) {

    // Opens rom file, gets file size in bytes
    FILE *f = fopen("./roms/pokemon-blue.gb", "rb");
    fseek(f, 0, SEEK_END);
    size_t fileSize = ftell(f);
    rewind(f);

    // Allocates space for rom in memory
    uint8_t *rom = malloc(fileSize);
    fread(rom, 1, fileSize, f);

    // Prints title bytes 
    printf("Title:\t");
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

    fclose(f);

}

/*
 * Function:	get_cart_type(type)
 *
 * Purpose:	Returns string representing the cartridge type, based
 *		on input cartridge type byte (as found in rom header)
 * 
 * Parameters:	type	-- Byte representing cartridge type
 */
const char *get_cart_type(uint8_t type) {
    switch (type) {
        case 0x00: return "ROM ONLY";
        case 0x01: return "MBC1";
        case 0x02: return "MBC1+RAM";
        case 0x03: return "MBC1+RAM+BATTERY";
        case 0x05: return "MBC2";
        case 0x06: return "MBC2+BATTERY";
        case 0x08: return "ROM+RAM";
        case 0x09: return "ROM+RAM+BATTERY";
        case 0x0B: return "MMM01";
        case 0x0C: return "MMM01+RAM";
        case 0x0D: return "MMM01+RAM+BATTERY";
        case 0x0F: return "MBC3+TIMER+BATTERY";
        case 0x10: return "MBC3+TIMER+RAM+BATTERY";
        case 0x11: return "MBC3";
        case 0x12: return "MBC3+RAM";
        case 0x13: return "MBC3+RAM+BATTERY";
        case 0x19: return "MBC5";
        case 0x1A: return "MBC5+RAM";
        case 0x1B: return "MBC5+RAM+BATTERY";
        case 0x1C: return "MBC5+RUMBLE";
        case 0x1D: return "MBC5+RUMBLE+RAM";
        case 0x1E: return "MBC5+RUMBLE+RAM+BATTERY";
        case 0x20: return "MBC6";
        case 0x22: return "MBC7+SENSOR+RUMBLE+RAM+BATTERY";
        case 0xFC: return "POCKET CAMERA";
        case 0xFD: return "BANDAI TAMA5";
        case 0xFE: return "HuC3";
        case 0xFF: return "HuC1+RAM+BATTERY";
        default:   return "UNKNOWN";
    }
}

/*
 * Function:	get_rom_size(val)
 *
 * Purpose:	Returns how much ROM is present on cartridge
 *		based off of ROM size byte in header
 * 
 * Parameters:	val	-- Byte representing ROM size byte (0x0148)
 */
uint32_t get_rom_size(uint8_t val) {
    if (val <= 0x08)
        return 32768 << val; 	    // 32KiB × (1 << val)
    switch (val) {
        case 0x52: return 1153434;  // 1.1 MiB
        case 0x53: return 1258291;  // 1.2 MiB
        case 0x54: return 1572864;  // 1.5 MiB
        default:   return 0;
    }
}
