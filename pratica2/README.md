# Prática 2 - SEL0630: Projetos em Sistemas Embarcados

Repositório destinado à entrega do trabalho 3 da disciplina SEL0630 - Projetos em Sistemas Embarcados. O trabalho foi dividido em três partes, conforme especificado no roteiro. A seguir, detalhamos a implementação de cada parte do trabalho.

## Estrutura de Diretórios
```bash
.
├── parte1
│   ├── led_control.py
│   └── timing.py
├── parte2
│   ├── ldr.py
│   └── pwm.py
└── parte3
    └── token_ring.py
```

## Parte 1: Programação em GPIO e Contagem Regressiva
Nesta parte, desenvolvemos dois scripts principais:
- **led_control.py**: Controla o LED através de um botão. O LED acende ou apaga dependendo do estado do botão pressionado.
- **timing.py**: Realiza uma contagem regressiva a partir de um valor digitado no terminal. Ao final da contagem, o LED acende, indicando o fim do tempo.

### Execução
Para executar os scripts da Parte 1:
```bash
python parte1/led_control.py
python parte1/timing.py
```

### Fotos e vídeos
_Aguardando inserção_

---

## Parte 2: Controle de Brilho com PWM e Sensores
- **pwm.py**: Controla o brilho de um LED utilizando PWM, variando o duty cycle de forma contínua.
- **ldr.py**: Utiliza um sensor LDR para medir a luz ambiente e plota em tempo real os valores lidos.

### Execução
Para executar os scripts da Parte 2:
```bash
python parte2/pwm.py
python parte2/ldr.py
```

### Fotos e vídeos
_Aguardando inserção_

---

## Parte 3: Aplicação com Multithreading - Token Ring com LEDs
Nesta parte, implementamos uma simulação de um Token Ring utilizando LEDs. Cada LED representa um "nó" do anel e acende em sequência, simulando a passagem de um token. A aplicação utiliza threads para gerenciar o funcionamento paralelo.

- **token_ring.py**: Implementa o token ring usando multithreading com mutexes para controlar o acendimento dos LEDs.

### Execução
Para executar o script da Parte 3:
```bash
python parte3/token_ring.py
```

### Fotos e vídeos
_Aguardando inserção_

---

## Como Executar

Para executar os scripts, siga as instruções abaixo:

1. Clone este repositório:
   ```bash
   git clone https://github.com/seuusuario/trabalho3-sistemas-embarcados.git
   ```
2. Acesse o diretório do trabalho:
   ```bash
   cd trabalho3-sistemas-embarcados
   ```
3. Execute o script desejado conforme a parte correspondente.

### Pré-requisitos

- Python 3.x
- Bibliotecas:
  - RPi.GPIO
  - gpiozero
  - matplotlib (para `ldr.py`)

---

## Integrantes

- Nome: Carlos Henrique Craveiro Aquino Veras - NUSP: 12547187
- Nome: Matheus Henrique Dias Cirilo - NUSP: 12547750
