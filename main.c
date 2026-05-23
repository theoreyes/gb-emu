#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "cart.h"

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