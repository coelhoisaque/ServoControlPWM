# ServoControlPWM 

Projeto de controle de servomotor via PWM no Raspberry Pi Pico W, integrado a um LED para feedback visual. Desenvolvido em C com Pico SDK e simulado no Wokwi.

## Funcionalidades Principais 💡
1. **Controle PWM de Servomotor**
   - Frequência de 50 Hz (período de 20 ms) no GPIO 22
   - Posições precisas: 0° (500µs), 90° (1470µs), 180° (2400µs)
   - Movimento suave com incrementos de 5µs a cada 10ms

2. **Sistema de Feedback com LED**
   - **LED Ligado**: Servo em 180°
   - **LED Piscando**: Servo em 90°
   - **LED Apagado**: Servo em 0°
   - **LED Rápido**: Durante movimento contínuo

3. **Circuito Integrado**
   - Servomotor conectado ao GPIO 22
   - LED com resistor de 1kΩ no GPIO 12

<img src="https://raw.githubusercontent.com/coelhoisaque/ServoControlPWM/main/circuit_diagram.png" width="400" alt="Diagrama do Circuito">

## Como Executar 

### Pré-requisitos
- [VS Code](https://code.visualstudio.com/)
- [Extensão Wokwi para VS Code](https://docs.wokwi.com/vscode/getting-started)
- [Pico SDK](https://www.raspberrypi.com/documentation/microcontrollers/c-sdk.html)

### Como Executar o Projeto

**Configuração do Ambiente**:
   - Instale o VS Code e o Pico SDK.
   - Integre o simulador Wokwi ao VS Code
```bash
# 1. Clone o repositório
git clone https://github.com/coelhoisaque/ServoControlPWM.git
cd ServoControlPWM
```
- Abra o projeto no VS Code.
```bash
code .
```
- Compile o código usando o Pico SDK.
- Execute a simulação no Wokwi.
**Observação do Comportamento**:
   - Observe a movimentação do servomotor e o comportamento do LED RGB no simulador.
## Vídeo de Demonstração

  Assista ao vídeo de demonstração do projeto [aqui](https://youtu.be/6wdlqLGdoDs).
## Trechos Relevantes do Código 

### Controle do Servomotor
```c
void set_servo_position(uint slice_num, uint channel, uint pulse_width_us) {
    uint32_t wrap = 125000000 / PWM_FREQ / 16;
    uint32_t level = (pulse_width_us * wrap) / 20000;
    pwm_set_chan_level(slice_num, channel, level);
}
```

### Lógica do LED
```c
// Durante movimento contínuo
for (int pulse = 500; pulse <= 2400; pulse += 5) {
    gpio_put(LED_PIN, !gpio_get(LED_PIN));  // Alternância rápida
    set_servo_position(slice_num, channel, pulse);
    sleep_ms(10);
}
```

## Resultados Esperados 📊
| Estado do Sistema  | Comportamento do LED | Posição do Servo |
| ------------------ | -------------------- | ---------------- |
| Inicialização      | Pisca 1x             | -                |
| Posição 180°       | Ligado continuamente | 2400µs           |
| Posição 90°        | Pisca a cada 250ms   | 1470µs           |
| Posição 0°         | Desligado            | 500µs            |
| Movimento Contínuo | Pisca a cada 10ms    | 500µs ↔ 2400µs   |

## Licença 
Este projeto é licenciado sob [MIT License](https://mit-license.org/) - consulte o arquivo LICENSE para detalhes.

