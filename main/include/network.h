#pragma once

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event.h"
#include "nvs_flash.h"

#define WIFI_SCAN_LIST_SIZE 5
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

void network_init(void);
uint16_t network_wifi_scan(wifi_ap_record_t *);
void network_connect(uint8_t ssid[32],uint8_t password[64],wifi_auth_mode_t authmode);