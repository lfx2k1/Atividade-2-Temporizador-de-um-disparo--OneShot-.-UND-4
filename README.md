# Atividade-2-Temporizador-de-um-disparo-OneShot-UND-4
Repositório para atividade de Temporizador One Shot do programa de Sistemas Embarcados, Embarcatech.

## Descrição
Este projeto implementa um sistema de temporização para acionamento de LEDs a partir do clique em um botão (pushbutton), utilizando o Raspberry Pi Pico W. O acionamento dos LEDs segue uma sequência pré-determinada, com transições baseadas em temporização usando a função add_alarm_in_ms().

Os LEDs utilizados são:

Verde (GPIO 11)
Azul (GPIO 12)
Vermelho (GPIO 13)
O botão de entrada está conectado à GPIO 5.

## Funcionamento
Quando o usuário pressiona o botão (pushbutton), os três LEDs são ligados simultaneamente.
1) Após 3 segundos, um dos LEDs é desligado, permanecendo apenas dois LEDs ligados.
2) Após mais 3 segundos, apenas um LED permanece ligado.
3) Depois de mais 3 segundos, todos os LEDs são desligados e o sistema volta ao estado inicial.
4) Durante a sequência de temporização, o botão não altera o estado dos LEDs. Somente após o ciclo completo (quando todos os LEDs estiverem apagados),um novo ciclo pode ser iniciado, caso o push button seja acionado.
5) O código foi testado e validado na ferramenta educacional BitDogLab.

## Utilização do programa

## 1. Pré-requisitos
Antes de rodar o programa, certifique-se de ter os seguintes itens configurados:
Placa: Raspberry Pi Pico W.
Ambiente de desenvolvimento: SDK do Raspberry Pi Pico configurado (CMake, GCC ARM, etc.).
Cabo USB: Para alimentação e comunicação serial com o Raspberry Pi Pico.

## 2. Compilação e Upload
Clone este repositório: git clone https://github.com/lfx2k1/Atividade-2-Temporizador-de-um-disparo-OneShot-UND-4.git

cd Atividade-2-Atividade-2-Temporizador-de-um-disparo-OneShot-UND-4

Compile o código

Após a compilação, um arquivo .uf2 será gerado. Para enviá-lo ao Raspberry Pi Pico:
Conecte o Raspberry Pi Pico ao PC segurando o botão BOOTSEL.
Ele será montado como um dispositivo de armazenamento.
Copie o arquivo .uf2 gerado para dentro do Raspberry Pi Pico.

## 3. Execução
Assim que o código for carregado, o sistema ficará aguardando um clique no botão (pushbutton).
Após o clique, os LEDs seguirão a sequência programada.
