#include <stdio.h>
#include "nvs_flash.h"
#include "esp_log.h"
static const char* TAG = "nvs_app";
nvs_handle_t nvsHandle;

void app_main(void)
{
   
   nvs_flash_init();

   esp_err_t err = nvs_open("namespace", NVS_READWRITE, &nvsHandle);
   nvs_set_str(nvsHandle, "stringa", "Test memoria flash");
   nvs_commit(nvsHandle);

    size_t required_size = 0;
    err = nvs_get_str(nvsHandle, "stringa", NULL, &required_size); 
    char* buff = malloc(required_size); 
        if (buff == NULL) {
            ESP_LOGE(TAG, "Errore nell'allocazione della memoria");
        } else {
            err = nvs_get_str(nvsHandle, "stringa", buff, &required_size);
            if (err == ESP_OK) {
                ESP_LOGI(TAG, "La stringa è: %s", buff);
            } else {
                ESP_LOGE(TAG, "Errore nel recupero della stringa (%s)", esp_err_to_name(err));
            }
            free(buff); 
        }

    nvs_close(nvsHandle);
    ESP_LOGI(TAG, "nvs closed");

}