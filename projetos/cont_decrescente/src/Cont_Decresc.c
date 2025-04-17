#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"

// Definição dos pinos
#define PINO_BOTAO_A 5
#define PINO_BOTAO_B 6
#define PINO_I2C_SDA 14
#define PINO_I2C_SCL 15

// Variável volátil para controle de reset via interrupção
volatile bool flag_reset = true;

// Buffer para mensagens do contador regressivo
const char *MENSAGENS_CONTADOR[] = {
    "9", "8", "7", "6", 
    "5", "4", "3", "2", 
    "1", "0"
};

// Callback para interrupção do botão A
void callback_botao_A(uint gpio, uint32_t eventos) {
    if (gpio == PINO_BOTAO_A && (eventos & GPIO_IRQ_EDGE_FALL)) {
        flag_reset = true;
    }
}

int main() {
    // Inicialização do hardware
    stdio_init_all();

    // Configuração do botão A com interrupção
    gpio_init(PINO_BOTAO_A);
    gpio_set_dir(PINO_BOTAO_A, GPIO_IN);
    gpio_pull_up(PINO_BOTAO_A);
    gpio_set_irq_enabled_with_callback(PINO_BOTAO_A, GPIO_IRQ_EDGE_FALL, true, &callback_botao_A);

    // Configuração do botão B
    gpio_init(PINO_BOTAO_B);
    gpio_set_dir(PINO_BOTAO_B, GPIO_IN);
    gpio_pull_up(PINO_BOTAO_B);

    // Configuração do display OLED
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(PINO_I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(PINO_I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(PINO_I2C_SDA);
    gpio_pull_up(PINO_I2C_SCL);
    ssd1306_init();

    // Área de renderização do display
    struct render_area area_display = {
        .start_column = 0,
        .end_column = ssd1306_width - 1,
        .start_page = 0,
        .end_page = ssd1306_n_pages - 1
    };
    calculate_render_area_buffer_length(&area_display);

    // Buffers para display e texto
    uint8_t buffer_display[ssd1306_buffer_length];
    char buffer_texto[32];
    memset(buffer_display, 0, ssd1306_buffer_length);
    render_on_display(buffer_display, &area_display);

    // Posicionamento do texto (centralizado)
    const int POS_X_TITULO = 0;
    const int POS_Y_TITULO = 0;
    const int POS_X_CONTADOR = 64;  // Centralizado horizontalmente
    const int POS_Y_CONTADOR = 16;  // Centralizado verticalmente
    const int POS_X_CLIQUES = 0;
    const int POS_Y_CLIQUES = 0;

    // Variáveis de estado
    bool estado_anterior_botao_B = true;
    uint16_t contador_cliques = 0;

    while (true) {
        if (flag_reset) {
            // Reset do sistema
            flag_reset = false;
            contador_cliques = 0;

            // Loop do contador regressivo
            for (size_t i = 0; i < (sizeof(MENSAGENS_CONTADOR) / sizeof(MENSAGENS_CONTADOR[0])); i++) {
                // Limpa e atualiza o display
                memset(buffer_display, 0, ssd1306_buffer_length);
                ssd1306_draw_string(buffer_display, POS_X_TITULO, POS_Y_TITULO, "Contador:");
                ssd1306_draw_string(buffer_display, POS_X_CONTADOR, POS_Y_CONTADOR, MENSAGENS_CONTADOR[i]);
                sprintf(buffer_texto, "Cliques: %d", contador_cliques);
                ssd1306_draw_string(buffer_display, POS_X_CLIQUES, POS_Y_CLIQUES, buffer_texto);
                render_on_display(buffer_display, &area_display);

                // Temporização de 1 segundo com verificação de botões
                uint32_t tempo_inicio = to_ms_since_boot(get_absolute_time());
                while (to_ms_since_boot(get_absolute_time()) - tempo_inicio < 1000) {
                    bool estado_atual_botao_B = gpio_get(PINO_BOTAO_B);

                    // Detecção de borda de descida no botão B
                    if (!estado_atual_botao_B && estado_anterior_botao_B) {
                        contador_cliques++;
                        // Atualização imediata do display quando o botão é pressionado
                        memset(buffer_display, 0, ssd1306_buffer_length);
                        ssd1306_draw_string(buffer_display, POS_X_TITULO, POS_Y_TITULO, "Contador:");
                        ssd1306_draw_string(buffer_display, POS_X_CONTADOR, POS_Y_CONTADOR, MENSAGENS_CONTADOR[i]);
                        sprintf(buffer_texto, "Cliques: %d", contador_cliques);
                        ssd1306_draw_string(buffer_display, POS_X_CLIQUES, POS_Y_CLIQUES, buffer_texto);
                        render_on_display(buffer_display, &area_display);
                    }
                    estado_anterior_botao_B = estado_atual_botao_B;

                    // Verificação rápida do botão A para reset imediato
                    if (!gpio_get(PINO_BOTAO_A)) {
                        sleep_ms(50);  // Debounce
                        flag_reset = true;
                        goto fim_contador;  // Sai do loop for
                    }

                    sleep_ms(10);
                }
            }
            fim_contador:;
        }

        tight_loop_contents();
    }
}