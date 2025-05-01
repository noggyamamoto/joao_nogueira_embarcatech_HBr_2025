#include <math.h>
#include "include/unity.h"

// Declaração da função a ser testada
float adc_para_celsius(uint16_t valor_adc);

// Teste para verificar conversão de um valor conhecido
void teste_adc_para_celsius_valor_conhecido(void) {
    // 0.706V corresponde a 27°C
    // valor_adc = (0.706 / 3.3) * 4096 ≈ 876
    uint16_t valor_adc = 876;
    float temperatura = adc_para_celsius(valor_adc);
    // Verifica se o valor convertido está dentro de 0.1°C do esperado
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 27.0f, temperatura);
}

// Função executada antes de cada teste (vazia neste caso)
void setUp(void) {}

// Função executada após cada teste (vazia neste caso)
void tearDown(void) {}

int main(void) {
    UNITY_BEGIN();  // Inicializa framework de teste
    RUN_TEST(teste_adc_para_celsius_valor_conhecido); // Executa teste
    return UNITY_END(); // Finaliza testes e relata resultados
}