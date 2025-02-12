#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22   // GPIO 22 conectado ao PWM do servomotor
#define PWM_FREQ 50   // Frequência de 50 Hz (período de 20 ms)
#define LED_PIN 12   // GPIO 12 para o LED RGB (BitDogLab)

void set_servo_position(uint slice_num, uint channel, uint pulse_width_us) {
    // Calcula o valor do ciclo ativo (duty cycle) com base no tempo de pulso em microssegundos
    uint32_t wrap = 125000000 / PWM_FREQ / 16;  // 125 MHz / 50 Hz / 16 (divisor de clock)
    uint32_t level = (pulse_width_us * wrap) / 20000;  // 20000 us = 20 ms (período)
    pwm_set_chan_level(slice_num, channel, level);
}

int main() {
    stdio_init_all();

    // Configuração do PWM para o servo
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);
    uint channel = pwm_gpio_to_channel(SERVO_PIN);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 16.0f);  // Divisor de clock = 16
    pwm_config_set_wrap(&config, 125000000 / PWM_FREQ / 16);  // Wrap para 50 Hz (20ms)
    pwm_init(slice_num, &config, true);

    // Configuração do LED na GPIO 12
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) {
        // Posição 180° (LED LIGADO)
        gpio_put(LED_PIN, 1);                // LED aceso
        set_servo_position(slice_num, channel, 2400);  // 2400 µs
        sleep_ms(5000);

        // Posição 90° (LED PISCANDO)
        gpio_put(LED_PIN, 0);                // LED apagado
        sleep_ms(250);
        gpio_put(LED_PIN, 1);                // LED aceso
        set_servo_position(slice_num, channel, 1470);  // 1470 µs
        sleep_ms(5000);

        // Posição 0° (LED DESLIGADO)
        gpio_put(LED_PIN, 0);                // LED apagado
        set_servo_position(slice_num, channel, 500);   // 500 µs
        sleep_ms(5000);

        // Movimento suave (LED PISCANDO RAPIDAMENTE)
        for (int pulse = 500; pulse <= 2400; pulse += 5) {
            gpio_put(LED_PIN, !gpio_get(LED_PIN));  // Alterna estado do LED
            set_servo_position(slice_num, channel, pulse);
            sleep_ms(10);
        }
        for (int pulse = 2400; pulse >= 500; pulse -= 5) {
            gpio_put(LED_PIN, !gpio_get(LED_PIN));  // Alterna estado do LED
            set_servo_position(slice_num, channel, pulse);
            sleep_ms(10);
        }
    }
}