# Leitura do Sensor de Temperatura Interno do RP2040

Este projeto realiza a leitura do sensor de temperatura interno do Raspberry Pi Pico (RP2040) e exibe os valores no terminal serial, incluindo testes unitários para validação da conversão ADC.

## 📋 Objetivo
Implementar um sistema que:
- Lê o sensor de temperatura interno do RP2040
- Converte o valor ADC para temperatura em graus Celsius
- Exibe os dados formatados no terminal serial
- Inclui testes unitários para garantir a precisão da conversão

## 🛠️ Lista de Materiais
| Componente          | Observação                          |
|---------------------|-------------------------------------|
| Raspberry Pi Pico   | Utiliza sensor interno do RP2040    |
| Cabo USB            | Para alimentação e comunicação serial |

## 📁 Estrutura do Projeto
- `main.c`: Lógica principal de leitura do sensor e conversão
- `temp_teste.c`: Testes unitários para função de conversão
- `CMakeLists.txt`: Configuração de compilação (a ser criado)

## 🔧 Funcionalidades
- Leitura periódica do sensor (500ms)
- Conversão precisa usando fórmula oficial do RP2040
- Saída formatada no terminal serial
- Testes automatizados para validação

## 📜 Licença
MIT License - [MIT]

## 🚀 Como Executar Testes Unitários

```bash
gcc temp_teste.c -I. -lunity -lm -o testes
./testes
```
### Programa Principal
1. Conecte o Raspberry Pi Pico via USB
2. Compile e envie o código:
```bash
mkdir build
cd build
cmake ..
make
