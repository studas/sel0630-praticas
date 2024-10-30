# Prática 4 - SEL0630: Projetos em Sistemas Embarcados

Repositório destinado à entrega da prática 5 da disciplina SEL0630 - Projetos em Sistemas Embarcados. A seguir, detalhamos a implementação de cada parte do trabalho.

## Estrutura de Diretórios
```bash
.
├── car-lights
│   ├── main
│   │   └── main.cpp
│   └── components
│       ├── adc_task
│       ├── button_task
│       └── light_control
```

---

## Prática
A prática envolveu a simulação do sistema de controle de luzes de um carro, onde o objetivo era ter um sistema bem componentizado que conseguisse controlar a intensidade e a ativação manual e automática da luz do carro.

### Execução
Utilize a biblioteca da ESP-IDF v5.1.2-2 para compilar o código e gravar na placa ESP32.

### Materiais
- 1x ESP32;
- 1x Protoboard;
- 1x Botão;
- 1x LDR;
- 1x Potenciometro;
- 2x Led;
- 2x Resistor 220 Ohm;
- 1x Resistor 10k Ohm.

### Fotos e vídeos
![montagem](https://github.com/studas/sel0630-praticas/blob/main/pratica5/images_nd_videos/montagem.jpeg)
![demonstracao](https://github.com/studas/sel0630-praticas/blob/main/pratica5/images_nd_videos/demonstracao.mp4)

### Melhorias futuras
- O sistema automático deve ter as seguintes funcionalidades:
  - Controle de intensidade de luzes de acordo com a luminosidade do ambiente;
  - Caso o usuário desative ele, o sistema deve manter a última configuração de intensidade;
- O sistema deve voltar no último estado depois de desligado;
- O sistema deve ativar e desativar tudo por meio de funções que poderiam ser chamadas externamente.

---

## Como Executar

Para executar os scripts, siga as instruções abaixo:

1. Clone este repositório:
   ```bash
   git clone https://github.com/studas/sel0630-praticas.git
   ```
2. Acesse o diretório do trabalho:
   ```bash
   cd sel0630-praticas/pratica5
   ```
3. Compile e envie para a ESP32.

### Pré-requisitos

- ESP-IDF v5.1.2-2

---

## Integrantes

- Nome: Carlos Henrique Craveiro Aquino Veras - NUSP: 12547187
- Nome: Matheus Henrique Dias Cirilo - NUSP: 12547750
