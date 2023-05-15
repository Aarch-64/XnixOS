#include <stdio.h>
#include <arch/i686/io.h>

#include "floppy.h"

void floppy_wait_for_ready() {
    while (1) {
        uint8_t status = i686_inb(FLOPPY_STATUS_PORT);
        if (!(status & FLOPPY_STATUS_BUSY_BIT))
            break;
    }
}

void floppy_send_command(uint8_t cmd) {
    floppy_wait_for_ready();
    i686_outb(FLOPPY_COMMAND_PORT, cmd);
}

void floppy_read_sector(uint8_t head, uint8_t track, uint8_t sector, uint8_t* buffer) {
    floppy_send_command(FLOPPY_CMD_SPECIFY);
    floppy_send_command(FLOPPY_CMD_READ_TRACK);

    floppy_wait_for_ready();
    i686_outb(FLOPPY_COMMAND_PORT, head << 2 | 0);  // Head and drive select
    i686_outb(FLOPPY_COMMAND_PORT, track);          // Track
    i686_outb(FLOPPY_COMMAND_PORT, head);           // Head
    i686_outb(FLOPPY_COMMAND_PORT, sector);         // Sector
    i686_outb(FLOPPY_COMMAND_PORT, 2);              // Size (512 bytes)

    floppy_wait_for_ready();

    for (int i = 0; i < 512; i++) {
        buffer[i] = i686_inb(FLOPPY_DATA_PORT);
    }
}

void print_sector_floppy_data(uint8_t* buffer, int size) {
    for (int i = 0; i < size; i++) {
        printf("%02X ", buffer[i]);
        if ((i + 1) % 16 == 0)
            printf("\n");
    }
}
