#pragma once
#include <stdint.h>

#define FLOPPY_DATA_PORT       0x3F5
#define FLOPPY_STATUS_PORT     0x3F4
#define FLOPPY_COMMAND_PORT    0x3F4

#define FLOPPY_CMD_SPECIFY     0x03
#define FLOPPY_CMD_READ_TRACK  0x02
#define FLOPPY_CMD_READ_SECTOR 0x06

#define FLOPPY_STATUS_BUSY_BIT 0x10
#define FLOPPY_STATUS_DATA_BIT 0x80

void floppy_read_sector(uint8_t head, uint8_t track, uint8_t sector, uint8_t* buffer);
void print_sector_floppy_data(uint8_t* buffer, int size);
