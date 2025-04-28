#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define ADC_REF_VOLTAGE 3.3f
#define ADC_RESOLUTION 4095.0f
#define TEMP_SENSOR_OFFSET 0.706f
#define TEMP_SENSOR_COEFF 0.001721f
#define BASE_TEMPERATURE 27.0f
#define READING_DELAY_MS 500

int main() {
    // Inicialização da comunicação serial
    stdio_init_all();
    
    // Aguarda conexão serial (útil para depuração)
    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }
    
    printf("\nIniciando leitura do sensor de temperatura interno do RP2040\n\n");

    // Configuração do ADC
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);  // Canal 4 para o sensor de temperatura

    while (true) {
        // Leitura do valor do ADC
        uint16_t raw_value = adc_read();
        
        // Cálculo da tensão
        float voltage = raw_value * ADC_REF_VOLTAGE / ADC_RESOLUTION;
        
        // Cálculo da temperatura (fórmula do datasheet)
        float temperature = BASE_TEMPERATURE - (voltage - TEMP_SENSOR_OFFSET) / TEMP_SENSOR_COEFF;
        
        // Exibição formatada dos resultados
        printf("Leitura ADC: %4u | Tensão: %.3f V | Temperatura: %.2f ºC\n", 
               raw_value, voltage, temperature);
        
        // Intervalo entre leituras
        sleep_ms(READING_DELAY_MS);
    }

    return 0;
}