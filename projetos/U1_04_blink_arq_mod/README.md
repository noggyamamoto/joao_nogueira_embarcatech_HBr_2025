# Projeto: Piscar LED Embutido na Raspberry Pi Pico W

Este projeto implementa uma estrutura modular para fazer o LED embutido da **Raspberry Pi Pico W** piscar indefinidamente. O código é organizado seguindo boas práticas de separação por camadas: *drivers*, *HAL (Hardware Abstraction Layer)* e *aplicação*.

## 🧱 Estrutura do Projeto

projeto/

├── app/

│   └── main.c

├── drivers/

│   └── led_embutido.c

├── hal/

│   └── hal_led.c

├── include/

│   ├── led_embutido.h

│   └── hal_led.h

└── CMakeLists.txt

## 📁 Descrição dos Componentes

### `drivers/led_embutido.c`
Contém código que interage diretamente com o hardware, usando a API `cyw43_arch` para controlar o LED embutido da Pico W.

### `hal/hal_led.c`
Implementa a função `hal_led_toggle()`, que fornece uma interface de alto nível para manipular o LED sem expor detalhes da API de hardware.

### `app/main.c`
Arquivo principal da aplicação. Utiliza a HAL para alternar o estado do LED com um intervalo de 500 ms, criando o efeito de piscar.

### `include/*.h`
Arquivos de cabeçalho contendo declarações das funções expostas por `hal_led.c` e `led_embutido.c`.

### `CMakeLists.txt`
Responsável por configurar a compilação do projeto, incluindo diretórios relevantes e arquivos-fonte.

## 🚀 Como Compilar

1. Clone ou copie a estrutura do projeto.
2. Configure o SDK do Pico (PICO_SDK_PATH).
3. Crie um diretório de build e compile:

```bash
mkdir build
cd build
cmake ..
make
