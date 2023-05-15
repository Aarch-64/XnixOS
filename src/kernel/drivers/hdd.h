#pragma once
#include <stdint.h>

#define HDD_DATA_PORT 0x1F0
#define HDD_ERROR_PORT 0x1F1
#define HDD_SECTOR_COUNT_PORT 0x1F2
#define HDD_SECTOR_NUMBER_PORT 0x1F3
#define HDD_CYLINDER_LOW_PORT 0x1F4
#define HDD_CYLINDER_HIGH_PORT 0x1F5
#define HDD_DRIVE_HEAD_PORT 0x1F6
#define HDD_COMMAND_PORT 0x1F7
#define HDD_STATUS_PORT 0x1F7

#define HDD_STATUS_ERROR_BIT 0x01
#define HDD_STATUS_BUSY_BIT 0x80

void hdd_read_sector(uint32_t sector, uint8_t* buffer);
