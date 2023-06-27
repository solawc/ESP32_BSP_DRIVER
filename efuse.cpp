#include "efuse.h"
#include "esp_efuse.h"

esp_efuse_desc_t *des_efuse[1];
size_t efuse_out = 0;
uint8_t EFUSE_BIT = 0;
bool _is_efuse_mks = false;

void efuseRead(void) {

    EFUSE_BIT = 3;

    // des_efuse[0] = (esp_efuse_desc_t *)malloc(sizeof(esp_efuse_desc_t));

    des_efuse[0] = (esp_efuse_desc_t* ) heap_caps_malloc(sizeof(esp_efuse_desc_t), MALLOC_CAP_DEFAULT);

    for (int i=0; i<3; i++) {
        des_efuse[0]->efuse_block = EFUSE_BLK0;
        des_efuse[0]->bit_start = XPD_SDIO_REG + i;
        des_efuse[0]->bit_count = 1;
        esp_efuse_read_field_cnt((const esp_efuse_desc_t **)des_efuse, &efuse_out);
        if(efuse_out) EFUSE_BIT |= 1<<i;
    }

    free(des_efuse[0]);
    if(EFUSE_BIT != 0x7) {
        log_debug_msg("Error:Please use mg mother board!!");
        log_debug_msg("Error:Please restart!!");
        while(1);
    }
}

void efuseWrite(void) {

    esp_err_t err = ESP_OK;

    des_efuse[0] = (esp_efuse_desc_t* ) heap_caps_malloc(sizeof(esp_efuse_desc_t), MALLOC_CAP_DEFAULT);

    for (int i=0; i<3; i++) {
        des_efuse[0]->efuse_block = EFUSE_BLK0;
        des_efuse[0]->bit_start = XPD_SDIO_REG + i;
        des_efuse[0]->bit_count = 1;
        err = esp_efuse_write_field_cnt((const esp_efuse_desc_t **)des_efuse, 1);
        if(err != ESP_OK) return;
    }

    memset(des_efuse[0], 0, sizeof(des_efuse[0]));

    for (int i=0; i<3; i++) {
        des_efuse[0]->efuse_block = EFUSE_BLK0;
        des_efuse[0]->bit_start = XPD_SDIO_REG + i;
        des_efuse[0]->bit_count = 1;
        esp_efuse_read_field_cnt((const esp_efuse_desc_t **)des_efuse, &efuse_out);
        if(efuse_out) EFUSE_BIT |= 1<<i;
    }

    if(EFUSE_BIT != 0x7) {
        log_debug_msg("ESP eFuse failed, please try again.");
        return ;
    }

    log_debug_msg("ESP eFuse succeed!");
}


