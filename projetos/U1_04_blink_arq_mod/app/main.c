#include <stdio.h>
#include "pico/stdlib.h"
#include "include/hal_led.h"
#include "include/led_embutido.h"

int main() {
    stdio_init_all();
    led_embutido_init();

    while (true) {
        hal_led_toggle();
        sleep_ms(500);
    }

    return 0;
}