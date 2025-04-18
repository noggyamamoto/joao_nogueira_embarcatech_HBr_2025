# Leitura de Joystick com Raspberry Pi Pico

Este projeto implementa um sistema de leitura de joystick analógico com botão em um Raspberry Pi Pico.

## 📋 Objetivo
Criar um sistema que:
- Lê valores analógicos dos eixos X e Y
- Detecta pressionamentos do botão
- Exibe dados no terminal serial
- Pode ser expandido para display OLED

## 🛠️ Lista de Materiais
| Componente          | Conexão no Pico       |
|---------------------|-----------------------|
| Raspberry Pi Pico   | -                     |
| Joystick Analógico  | Eixo X: GPIO26 (ADC0) |
|                     | Eixo Y: GPIO27 (ADC1) |
|                     | Botão: GPIO22         |

## 🚀 Execução
1. Conecte o joystick aos pinos do Pico
2. Compile e envie o código:
```bash
mkdir build
cd build
cmake ..
make

## Arquivos Principais
- `src/main.c`: Código principal com toda a lógica
- `CMakeLists.txt`: Configuração do projeto

## Licença
MIT License - MIT GPL-3.0.