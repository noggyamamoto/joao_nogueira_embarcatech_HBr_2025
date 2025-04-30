#include "include/hal_led.h"
#include "include/led_embutido.h"

static bool led_state = false;

void hal_led_toggle(void) {
    led_state = !led_state;
    led_embutido_set(led_state);
}