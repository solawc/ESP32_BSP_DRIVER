#include "intel_fs.h"
#include "esp_partition.h"      // partition file

constexpr const char* spiffsName   = "spiffs";
constexpr const char* littlefsName = "littlefs";

static bool is_has_partition(const char* label) {

    auto part = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_ANY, label);
    return part != NULL;
} 


void loacalFsMount(void) {

#ifdef USE_FS_LITTLEFS
    if(!is_has_partition(littlefsName)) {
        grbl_send(CLIENT_SERIAL, "Error:no FS par.\n");
    }
#else
    if(!is_has_partition(spiffsName)) {
        grbl_send(CLIENT_SERIAL, "no SPIFFS.\n");
    }
#endif
}



