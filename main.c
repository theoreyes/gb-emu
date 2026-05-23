#include <stdio.h>
#include <stdint.h>

int main (int argc, char argv**) {

    // Opens rom file, gets file size in bytes
    FILE *f = fopen("/roms/tetris.gb", "rb");
    fseek(f, 0, SEEK_END);
    size_t fileSize = ftell(f);
    rewind(f);

    // Allocates space for rom in memory
    uint8_t *rom = malloc(fileSize);
    fread(rom, 1, fileSize, f);

    // Prints title bytes 
    for (int i = 0x0134; i <= 0x0143; i++) {
        if (rom[i] == '\0') break;
        printf("%c", rom[i]);
    }
    printf("\n");

    fclose(f);

}