# ServoControlPWM

Este projeto tem como objetivo controlar um servomotor utilizando modulação por largura de pulso (PWM) no microcontrolador RP2040 (Raspberry Pi Pico W). O código foi desenvolvido em C usando o Pico SDK e simulado no ambiente Wokwi.

## Requisitos

- **Hardware Simulado**:
  - Microcontrolador Raspberry Pi Pico W
  - Servomotor (motor micro servo padrão)

- **Software**:
  - VS Code
  - Pico SDK
  - Simulador Wokwi

## Funcionalidades

1. **Configuração do PWM**:
   - Frequência de 50 Hz (período de 20 ms) no GPIO 22.
   
2. **Posicionamento do Servomotor**:
   - Posição de 180 graus (2400 µs) com espera de 5 segundos.
   - Posição de 90 graus (1470 µs) com espera de 5 segundos.
   - Posição de 0 graus (500 µs) com espera de 5 segundos.

3. **Movimentação Suave**:
   - Movimentação periódica do braço do servomotor entre 0 e 180 graus com incrementos de 5 µs e atraso de 10 ms.

4. **Experimentação com LED RGB**:
   - Uso do GPIO 12 para observar o comportamento do LED RGB com o mesmo controle PWM.

## Como Executar o Projeto

1. **Configuração do Ambiente**:
   - Instale o VS Code e o Pico SDK.
   - Integre o simulador Wokwi ao VS Code.

2. **Clonar o Repositório**:
   ```bash
   git clone https://github.com/coelhoisaque/ServoControlPWM.git
   cd ServoControlPWM
   ```

3. **Compilar e Executar**:
   - Abra o projeto no VS Code.
   - Compile o código usando o Pico SDK.
   - Execute a simulação no Wokwi.

4. **Observação do Comportamento**:
   - Observe a movimentação do servomotor e o comportamento do LED RGB no simulador.

## Vídeo de Demonstração

Assista ao vídeo de demonstração do projeto [aqui]().


## Licença

Este projeto está licenciado sob a licença MIT. Veja o arquivo [LICENSE](https://mit-license.org/) para mais detalhes.




