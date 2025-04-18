#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"

// Definição de constantes para os pinos
#define PINO_BOTAO_JOYSTICK 22   // Pino digital para o botão do joystick
#define PINO_ADC_EIXO_X 26       // Pino analógico para o eixo X (ADC1)
#define PINO_ADC_EIXO_Y 27       // Pino analógico para o eixo Y (ADC0)

int main() {
    // Inicializa a comunicação serial (para printf)
    stdio_init_all();
    
    // Inicializa o hardware ADC (Conversor Analógico-Digital)
    adc_init();
    
    // Configura os pinos ADC para leitura dos eixos do joystick
    adc_gpio_init(PINO_ADC_EIXO_X);  // Configura GPIO26 como entrada analógica
    adc_gpio_init(PINO_ADC_EIXO_Y);  // Configura GPIO27 como entrada analógica
    
    // Configura o pino do botão do joystick
    gpio_init(PINO_BOTAO_JOYSTICK);          // Inicializa o pino GPIO
    gpio_set_dir(PINO_BOTAO_JOYSTICK, GPIO_IN);  // Define como entrada
    gpio_pull_up(PINO_BOTAO_JOYSTICK);       // Ativa resistor de pull-up interno

    // Loop principal infinito
    while (true) {
        // Lê o valor do eixo X (horizontal)
        adc_select_input(1);                 // Seleciona canal ADC1 (GPIO26)
        int valorEixoX = adc_read();         // Lê o valor bruto (0-4095 para 12 bits)

        // Lê o valor do eixo Y (vertical)
        adc_select_input(0);                 // Seleciona canal ADC0 (GPIO27)
        int valorEixoY = adc_read();         // Lê o valor bruto

        // Lê o estado do botão (lógica invertida por causa do pull-up)
        bool botaoPressionado = !gpio_get(PINO_BOTAO_JOYSTICK);
        
        // Exibe os valores lidos no terminal serial
        printf("Eixo X: %4d, Eixo Y: %4d, Botão: %s\n", 
               valorEixoX, valorEixoY, 
               botaoPressionado ? "Pressionado" : "Livre");
        
        // Pequeno delay para evitar leituras muito rápidas
        sleep_ms(200);
    }

    // O programa nunca chegará aqui devido ao loop infinito
    return 0;
}