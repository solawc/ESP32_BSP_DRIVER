#ifndef __efuse_h
#define __efuse_h

#include "../main.h"

typedef enum {
    XPD_SDIO_REG = 142,
    SDIO_TIEH,
    SDIO_FORCE,
}hal_efuse_bit_t;


void efuseRead(void);

#endif