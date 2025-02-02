#include <stdio.h> // Biblioteca padrão do C.
#include "pico/stdlib.h" // Biblioteca padrão do Raspberry Pi Pico para controle de GPIO, temporização e comunicação serial.
#include "pico/time.h"   // Biblioteca para gerenciamento de temporizadores e alarmes.

const uint LED_PIN_GREEN = 11;    // Define o pino GPIO 11 para controlar o LED VERDE.
const uint LED_PIN_BLUE = 12;    // Define o pino GPIO 12 para controlar o LED AZUL.
const uint LED_PIN_RED = 13;    // Define o pino GPIO 13 para controlar o LED VERMELHO.
const uint BUTTON_PIN = 5;  // Define o pino GPIO 5 para ler o estado do botão.

bool led_active = false;    // Indica se o LED está atualmente aceso (para evitar múltiplas ativações).

// Função de callback para desligar o LED verde após 3 segundos (3000 ms)
int64_t turn_off_green_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_PIN_GREEN, false); // Desliga o LED verde
    return 0;
}

// Função de callback para desligar o LED azul após 6 segundos (6000 ms)
int64_t turn_off_blue_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_PIN_BLUE, false); // Desliga o LED azul
    return 0;
}

// Função de callback para desligar o LED vermelho após 9 segundos (9000 ms)
int64_t turn_off_red_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_PIN_RED, false); // Desliga o LED vermelho
    led_active = false; // Atualiza o estado de 'led_active' para falso, indicando que todos os LEDs estão desligados
    return 0;
}

int main() {
    stdio_init_all(); // Inicializa a comunicação serial para permitir o uso de printf.

    // Configura os pinos 11, 12 e 13 dos LEDs como saída digital.
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);

    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);

    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);

    // Configura o pino BUTTON_PIN (5) como entrada digital.
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);

    // Habilita o resistor pull-up interno para o pino do botão.
    gpio_pull_up(BUTTON_PIN);

    // Loop principal do programa que verifica continuamente o estado do botão.
    while (true) {
        // Verifica se o botão foi pressionado (nível baixo no pino) e se o LED não está ativo.
        if (gpio_get(BUTTON_PIN) == 0 && !led_active) {
            // Adiciona um pequeno atraso para debounce, evitando leituras errôneas.
            sleep_ms(50);

            // Verifica novamente o estado do botão após o debounce.
            if (gpio_get(BUTTON_PIN) == 0) {
                // Liga os LEDs configurando os pinos 11, 12 e 13 para nível alto.
                gpio_put(LED_PIN_GREEN, true);
                gpio_put(LED_PIN_BLUE, true);
                gpio_put(LED_PIN_RED, true);

                // Define 'led_active' como true para indicar que os LEDs estão acesos.
                led_active = true;

                // Agenda os alarmes para desligar os LEDs em intervalos de 3 segundos.
                add_alarm_in_ms(3000, turn_off_green_callback, NULL, false);
                add_alarm_in_ms(6000, turn_off_blue_callback, NULL, false);
                add_alarm_in_ms(9000, turn_off_red_callback, NULL, false);
            }
        }

        // Introduz uma pequena pausa de 10 ms para reduzir o uso da CPU.
        sleep_ms(10);
    }

    // Retorno de 0, que nunca será alcançado devido ao loop infinito.
    return 0;
}
