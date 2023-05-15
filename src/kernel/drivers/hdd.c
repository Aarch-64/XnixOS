#include <stdio.h>
#include <arch/i686/io.h>

#include "hdd.h"

void hdd_wait_for_ready() {
    while (1) {
        uint8_t status = i686_inb(HDD_STATUS_PORT);
        if (!(status & HDD_STATUS_BUSY_BIT))
            break;
    }
}

void hdd_read_sector(uint32_t sector, uint8_t* buffer) {
    hdd_wait_for_ready();

    i686_outb(HDD_DRIVE_HEAD_PORT, 0xE0 | ((sector >> 24) & 0x0F));
    i686_outb(HDD_SECTOR_COUNT_PORT, 1);
    i686_outb(HDD_SECTOR_NUMBER_PORT, sector & 0xFF);
    i686_outb(HDD_CYLINDER_LOW_PORT, (sector >> 8) & 0xFF);
    i686_outb(HDD_CYLINDER_HIGH_PORT, (sector >> 16) & 0xFF);
    i686_outb(HDD_COMMAND_PORT, 0x20);

    hdd_wait_for_ready();

    for (int i = 0; i < 256; i++) {
        uint16_t data = i686_inw(HDD_DATA_PORT);
        buffer[i * 2] = data & 0xFF;
        buffer[i * 2 + 1] = (data >> 8) & 0xFF;
    }
}
