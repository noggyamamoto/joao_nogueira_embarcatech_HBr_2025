#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

// Função para converter valor ADC para temperatura em Celsius
float adc_para_celsius(uint16_t valor_adc) {
    const float fator_conversao = 3.3f / (1 << 12); // Fator para converter valor ADC para tensão (3.3V / 4096)
    float tensao = valor_adc * fator_conversao;     // Converte valor ADC para tensão
    return 27.0f - (tensao - 0.706f) / 0.001721f;  // Fórmula para converter tensão para temperatura
}

int main(void) {
    stdio_init_all();  // Inicializa comunicação serial

    // Configuração do ADC
    adc_init();                      // Inicializa o conversor analógico-digital
    adc_set_temp_sensor_enabled(true); // Habilita sensor de temperatura interno
    adc_select_input(4);             // Seleciona o canal do sensor de temperatura

    while(1) {
        uint16_t valor_bruto = adc_read();          // Lê valor bruto do ADC
        float temperatura = adc_para_celsius(valor_bruto); // Converte para temperatura
        printf("Temperatura = %f C\n", temperatura);       // Exibe temperatura
        sleep_ms(500);                             // Aguarda 1 segundo
    }
}