#ifndef MQTT_MAIN_H
#define MQTT_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif
static void  *pclient = NULL;

void mqtt_main_init(void);
int mqtt_main_publish(void *handle,  char *payload);
int mqtt_main_thread_init(void);
#ifdef __cplusplus
}
#endif

#endif // MQTT_MAIN_H
