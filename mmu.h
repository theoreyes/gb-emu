#ifndef MMU_H
#define MMU_H

    uint8_t read8(uint16_t addr);
    void mmu_load_rom(const char *path);

#endif