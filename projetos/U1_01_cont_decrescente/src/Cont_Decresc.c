#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"  // Biblioteca do display OLED

// Definição dos pinos utilizados
#define PINO_BOTAO_A 5     // Botão responsável por resetar a contagem
#define PINO_BOTAO_B 6     // Botão responsável por contar cliques
#define PINO_I2C_SDA 14    // Pino SDA do barramento I2C
#define PINO_I2C_SCL 15    // Pino SCL do barramento I2C

// Variáveis globais voláteis usadas em interrupções
volatile bool flag_reset = true;                 // Indica se o sistema deve ser reiniciado
volatile uint16_t contador_cliques = 0;          // Armazena a quantidade de cliques no botão B
volatile absolute_time_t ultimo_clique_b = {0};  // Marca o último tempo de clique (para debounce)

// Mensagens de contagem regressiva (strings com os números de 9 a 0)
const char *MENSAGENS_CONTADOR[] = {
    "9", "8", "7", "6", 
    "5", "4", "3", "2", 
    "1", "0"
};

// Função de callback para tratar interrupções dos botões A e B
void callback_botoes(uint gpio, uint32_t eventos) {
    if ((eventos & GPIO_IRQ_EDGE_FALL)) {  // Apenas na borda de descida
        if (gpio == PINO_BOTAO_A) {
            flag_reset = true;  // Botão A: reiniciar a contagem
        } else if (gpio == PINO_BOTAO_B) {
            absolute_time_t agora = get_absolute_time();
            // Debounce: só conta se passaram mais de 190ms do último clique
            if (absolute_time_diff_us(ultimo_clique_b, agora) > 190000) {
                contador_cliques++;
                ultimo_clique_b = agora;
            }
        }
    }
}

int main() {
    stdio_init_all();  // Inicializa entrada/saída padrão

    // Configuração do botão A
    gpio_init(PINO_BOTAO_A);
    gpio_set_dir(PINO_BOTAO_A, GPIO_IN);
    gpio_pull_up(PINO_BOTAO_A);

    // Configuração do botão B
    gpio_init(PINO_BOTAO_B);
    gpio_set_dir(PINO_BOTAO_B, GPIO_IN);
    gpio_pull_up(PINO_BOTAO_B);

    // Habilita interrupções para os dois botões, usando callback unificado
    gpio_set_irq_enabled_with_callback(PINO_BOTAO_A, GPIO_IRQ_EDGE_FALL, true, &callback_botoes);
    gpio_set_irq_enabled(PINO_BOTAO_B, GPIO_IRQ_EDGE_FALL, true);

    // Inicialização do barramento I2C e display OLED SSD1306
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(PINO_I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(PINO_I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(PINO_I2C_SDA);
    gpio_pull_up(PINO_I2C_SCL);
    ssd1306_init();  // Inicializa o display OLED

    // Define a área de renderização do display inteiro
    struct render_area area_display = {
        .start_column = 0,
        .end_column = ssd1306_width - 1,
        .start_page = 0,
        .end_page = ssd1306_n_pages - 1
    };
    calculate_render_area_buffer_length(&area_display);

    // Buffers de display e texto
    uint8_t buffer_display[ssd1306_buffer_length];
    char buffer_texto[32];

    // Posições para desenhar no display (ajustadas para 128x64)
    const int POS_X_TITULO = 30;      // Posição do título "Contador"
    const int POS_Y_TITULO = 0;
    const int POS_X_CONTADOR = 60;    // Número grande no meio da tela
    const int POS_Y_CONTADOR = 24;
    const int POS_X_CLIQUES = 27;     // Quantidade de cliques
    const int POS_Y_CLIQUES = 56;

    while (true) {
        if (flag_reset) {
            flag_reset = false;      // Reseta a flag
            contador_cliques = 0;    // Zera o número de cliques

            // Loop de contagem regressiva de 9 a 0
            for (size_t i = 0; i < (sizeof(MENSAGENS_CONTADOR) / sizeof(MENSAGENS_CONTADOR[0])); i++) {
                memset(buffer_display, 0, ssd1306_buffer_length);  // Limpa o buffer do display

                // Escreve as três informações principais no display
                ssd1306_draw_string(buffer_display, POS_X_TITULO, POS_Y_TITULO, "Contador");
                ssd1306_draw_string(buffer_display, POS_X_CONTADOR, POS_Y_CONTADOR, MENSAGENS_CONTADOR[i]);
                sprintf(buffer_texto, "Cliques: %d", contador_cliques);
                ssd1306_draw_string(buffer_display, POS_X_CLIQUES, POS_Y_CLIQUES, buffer_texto);

                // Renderiza no display
                render_on_display(buffer_display, &area_display);

                // Aguarda 1 segundo, verificando se o botão A é pressionado
                uint32_t tempo_inicio = to_ms_since_boot(get_absolute_time());
                while (to_ms_since_boot(get_absolute_time()) - tempo_inicio < 1000) {
                    if (!gpio_get(PINO_BOTAO_A)) {
                        sleep_ms(50);  // Debounce adicional
                        flag_reset = true;
                        goto fim_contador;  // Sai do loop da contagem
                    }
                    sleep_ms(10);  // Reduz uso de CPU
                }
            }
            fim_contador:;
        }

        tight_loop_contents();  // Otimiza o uso de energia e CPU no loop ocioso
    }
}
