#include "pico/cyw43_arch.h"
#include "include/led_embutido.h"

void led_embutido_init(void) {
    if (cyw43_arch_init()) {
        while (true); // Tratamento de erro: falha na inicialização
    }
}

void led_embutido_set(bool state) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, state);
}