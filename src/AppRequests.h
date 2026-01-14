#pragma once

#include <pebble.h>

// Initialisiert die App Message Kommunikation
void pebble_messenger_init(void);

// Sendet Username und Password an die Android App
void pebble_messenger_send_credentials(const char *username, const char *password);

// Cleanup-Funktion (optional, falls benötigt)
void pebble_messenger_deinit(void);