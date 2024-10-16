# Prática 4 - SEL0630: Projetos em Sistemas Embarcados

Repositório destinado à entrega da prática 4 da disciplina SEL0630 - Projetos em Sistemas Embarcados. A seguir, detalhamos a implementação de cada parte do trabalho.

## Estrutura de Diretórios
```bash
.
├── blink.service
├── blink.sh
├── led_blink.py

```

## Prática
Desenvolvemos um service para o Raspberry Pi que faz um LED piscar. Fizemos tanto uma versão com sh `blink.sh` quanto uma versão com Python `led_blink.py`.

### Execução
Para iniciar e parar o serviço, execute os comandos:
```bash
sudo systemctl start blink
sudo systemctl stop blink
```

Para cadastrar o serviço na inicialização, execute o comando:
```bash
sudo cp blink.service /etc/systemd/system/
sudo systemctl enable blink
```

### Fotos e vídeos
![montagem](https://github.com/studas/sel0630-praticas/blob/main/pratica4/images_nd_videos/blink_service.jpeg)
![demonstracao](https://github.com/studas/sel0630-praticas/blob/main/pratica4/images_nd_videos/blink_service.mp4)

---

## Como Executar

Para executar os scripts, siga as instruções abaixo:

1. Clone este repositório:
   ```bash
   git clone https://github.com/studas/sel0630-praticas.git
   ```
2. Acesse o diretório do trabalho:
   ```bash
   cd sel0630-praticas/pratica4
   ```
3. Execute o script desejado conforme a parte correspondente.

### Pré-requisitos

- Python 3.x
- Bibliotecas:
  - RPi.GPIO

---

## Integrantes

- Nome: Carlos Henrique Craveiro Aquino Veras - NUSP: 12547187
- Nome: Matheus Henrique Dias Cirilo - NUSP: 12547750
