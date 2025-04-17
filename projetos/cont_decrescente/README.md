# Contador Regressivo com Interrupção

Este projeto implementa um contador decrescente controlado por interrupção em um Raspberry Pi Pico, demonstrando o uso de:
- Display OLED para visualização
- Botões para controle do sistema
- Temporização precisa com tratamento de interrupções

## Objetivo
Criar um sistema que:
1. Reinicia um contador regressivo (9→0) ao pressionar o Botão A
2. Registra pressionamentos do Botão B durante a contagem
3. Exibe ambos os valores no display OLED
4. Congela o sistema ao atingir zero até novo reset

## Lista de Materiais
| Componente          | Conexão no Pico |
|---------------------|-----------------|
| Raspberry Pi Pico   | -               |
| Display OLED I2C    | SDA: GPIO14     |
|                     | SCL: GPIO15     |
| Botão A             | GPIO5           |
| Botão B             | GPIO6           |

## Execução
1. Abra o projeto no VS Code com ambiente configurado para Raspberry Pi Pico
2. Compile o projeto (Ctrl+Shift+B no VS Code ou via terminal com `cmake` e `make`)
3. Conecte o Pico no modo BOOTSEL (segure BOOTSEL ao conectar USB)
4. Copie o arquivo `.uf2` gerado para a unidade RPI-RP2
5. O sistema iniciará automaticamente:
   - Aguardando pressionamento do Botão A para começar
   - Mostrando contagem e cliques no display

## Lógica de Funcionamento
1. **Interrupção do Botão A**:
   - Reinicia contador em 9
   - Zera contagem de cliques
   - Inicia contagem regressiva

2. **Contagem Regressiva**:
   - Decrementa o valor a cada 1 segundo
   - Atualiza display em tempo real

3. **Registro de Cliques**:
   - Durante a contagem, pressionamentos do Botão B são contados
   - Exibição imediata no display

4. **Estado Final**:
   - Ao chegar em 0, mostra:
     - Valor final do contador (0)
     - Total de cliques no Botão B
   - Aguarda novo reset pelo Botão A

## Arquivos Principais
- `src/main.c`: Código principal com toda a lógica
- `inc/ssd1306.h`: Driver para o display OLED
- `CMakeLists.txt`: Configuração do projeto  

## Licença
MIT License - © 2023 [Seu Nome]
