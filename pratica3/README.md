# Prática 3 - SEL0630: Projetos em Sistemas Embarcados

Repositório destinado à entrega da prática 3 da disciplina SEL0630 - Projetos em Sistemas Embarcados. O trabalho foi dividido em duas partes, conforme especificado no roteiro. A seguir, detalhamos a implementação de cada parte do trabalho.

## Estrutura de Diretórios
```bash
.
├── parte1
│   ├── led_control.py
│   ├── led_control
│   │   └── led_control.ino
│   ├── read_potentiometer.py
│   └── read_potentiometer
│       └── read_potentiometer.ino
└── parte2
    ├── acesso.py
    └── cadastro.py
```

## Parte 1: Comunicação serial I2C entre SBC/Linux embarcado e Microcontrolador
Nesta parte, desenvolvemos dois sistemas, contando com código para o microcontrolador Arduino e o driver para o Raspberry Pi.
- **led_control**: Controla o liga/desliga do LED através de um comando I2C enviado pelo Raspberry Pi.
- **read_potentiometer**: Lê o valor do potenciômetro e envia para o Raspberry Pi através de um comando I2C.

### Execução
Use a Arduino IDE para carregar os códigos `led_control.ino` e `read_potentiometer.ino` no microcontrolador. Em seguida, execute os scripts Python no Raspberry Pi:
```bash
python parte1/led_control.py
python parte1/read_potentiometer.py
```

### Fotos e vídeos
![circuito](https://github.com/studas/sel0630-praticas/blob/main/pratica3/images_nd_videos/arduino_and_raspberry.jpeg)
![led](https://github.com/studas/sel0630-praticas/blob/main/pratica3/images_nd_videos/led.mp4)
![potentiometer](https://github.com/studas/sel0630-praticas/blob/main/pratica3/images_nd_videos/potentiometer.mp4)
---

## Parte 2: Protocolo SPI e controle de acesso via Tags
- **cadastro**: Cadastra um cartão RFID para um determinado usuário na base de dados.
- **acesso**: Verifica um cartão RFID e libera o acesso se estiver na base de dados.

### Execução
Para executar os scripts da Parte 2:
```bash
python acesso.py
python cadastro.py
```

### Fotos e vídeos
![rfid](https://github.com/studas/sel0630-praticas/blob/main/pratica3/images_nd_videos/rfid.mp4)
![circuito](https://github.com/studas/sel0630-praticas/blob/main/pratica3/images_nd_videos/rfid.jpeg)
---

## Como Executar

Para executar os scripts, siga as instruções abaixo:

1. Clone este repositório:
   ```bash
   git clone https://github.com/studas/sel0630-praticas.git
   ```
2. Acesse o diretório do trabalho:
   ```bash
   cd sel0630-praticas/pratica3
   ```
3. Execute o script desejado conforme a parte correspondente.

### Pré-requisitos

- Python 3.x
- Bibliotecas:
  - RPi.GPIO
  - smbus
  - mfrc522

---

## Integrantes

- Nome: Carlos Henrique Craveiro Aquino Veras - NUSP: 12547187
- Nome: Matheus Henrique Dias Cirilo - NUSP: 12547750
