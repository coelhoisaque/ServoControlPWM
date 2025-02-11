#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22  // GPIO 22 conectado ao PWM do servomotor
#define PWM_FREQ 50   // Frequência de 50 Hz (período de 20 ms)

void set_servo_position(uint slice_num, uint channel, uint pulse_width_us) {
    // Calcula o valor do ciclo ativo (duty cycle) com base no tempo de pulso em microssegundos
    uint32_t wrap = 125000000 / PWM_FREQ / 16;  // 125 MHz / 50 Hz / 16 (divisor de clock)
    uint32_t level = (pulse_width_us * wrap) / 20000;  // 20000 us = 20 ms (período)
    pwm_set_chan_level(slice_num, channel, level);
}

int main() {
    stdio_init_all();

    // Configuração do PWM
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);
    uint channel = pwm_gpio_to_channel(SERVO_PIN);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 16.0f);  // Divisor de clock para 16
    pwm_config_set_wrap(&config, 125000000 / PWM_FREQ / 16);  // Wrap para 50 Hz
    pwm_init(slice_num, &config, true);

    // Movimentação do servomotor
    while (true) {
        // Posição 180 graus (2400 µs)
        set_servo_position(slice_num, channel, 2400);
        sleep_ms(5000);

        // Posição 90 graus (1470 µs)
        set_servo_position(slice_num, channel, 1470);
        sleep_ms(5000);

        // Posição 0 graus (500 µs)
        set_servo_position(slice_num, channel, 500);
        sleep_ms(5000);

        // Movimentação suave entre 0 e 180 graus
        for (int pulse_width = 500; pulse_width <= 2400; pulse_width += 5) {
            set_servo_position(slice_num, channel, pulse_width);
            sleep_ms(10);
        }
        for (int pulse_width = 2400; pulse_width >= 500; pulse_width -= 5) {
            set_servo_position(slice_num, channel, pulse_width);
            sleep_ms(10);
        }
    }
}