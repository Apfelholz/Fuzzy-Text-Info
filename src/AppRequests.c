#include "AppRequests.h"

// Callback wenn Nachricht erfolgreich gesendet wurde
static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Nachricht erfolgreich gesendet!");
}

// Callback wenn Senden fehlgeschlagen ist
static void outbox_failed_callback(DictionaryIterator *iterator, 
                                   AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Senden fehlgeschlagen: %d", (int)reason);
}

// Initialisiert die App Message Kommunikation
void pebble_messenger_init(void) {
  // Callbacks registrieren
  app_message_register_outbox_sent(outbox_sent_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  
  // Buffer-Größe festlegen (anpassen falls mehr Daten gesendet werden)
  app_message_open(128, 128);
  
  APP_LOG(APP_LOG_LEVEL_INFO, "Pebble Messenger initialisiert");
}

// Sendet Username und Password an die Android App
void pebble_messenger_send_credentials(const char *username, const char *password) {
  if (!username || !password) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Username oder Password ist NULL");
    return;
  }
  
  DictionaryIterator *iter;
  AppMessageResult result = app_message_outbox_begin(&iter);
  
  if (result != APP_MSG_OK) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Fehler beim Beginnen der Nachricht: %d", (int)result);
    return;
  }
  
  // Keys für die Daten (müssen mit Android App übereinstimmen)
  dict_write_cstring(iter, 0, username);  // Key 0 für username
  dict_write_cstring(iter, 1, password);  // Key 1 für password
  
  // Nachricht senden
  result = app_message_outbox_send();
  
  if (result != APP_MSG_OK) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Fehler beim Senden: %d", (int)result);
  } else {
    APP_LOG(APP_LOG_LEVEL_INFO, "Credentials werden gesendet...");
  }
}


