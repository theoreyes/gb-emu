#ifndef MMU_H
#define MMU_H

    uint8_t read8(uint16_t addr);
    void write8(uint16_t addr, uint8_t val);
    void mmu_load_rom(const char *path);

#endif