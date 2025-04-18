# Leitura do Sensor de Temperatura Interno do RP2040

Este projeto realiza a leitura do sensor de temperatura interno do Raspberry Pi Pico (RP2040) e exibe os valores no terminal serial.

## 📋 Objetivo
Implementar um sistema que:
- Lê o sensor de temperatura interno do RP2040
- Converte o valor ADC para temperatura em graus Celsius
- Exibe os dados formatados no terminal serial
- Fornece informações de tensão e valor ADC bruto

## 🛠️ Lista de Materiais
| Componente          | Observação                          |
|---------------------|-------------------------------------|
| Raspberry Pi Pico   | Utiliza sensor interno do RP2040    |
| Cabo USB            | Para alimentação e comunicação serial |

## 📁 Arquivo Principal
- `temperatura_interna.c`: Contém toda a lógica de leitura e conversão do sensor

## 📜 Licença
MIT License - [MIT]

## 🚀 Como Executar
1. Conecte o Raspberry Pi Pico via USB
2. Compile e envie o código:
```bash
mkdir build
cd build
cmake ..
make
