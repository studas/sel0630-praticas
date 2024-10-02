from mfrc522 import SimpleMFRC522
from time import sleep
import RPi.GPIO as GPIO
import csv

# Desabilitar os avisos
GPIO.setwarnings(False)

# Configuração dos pinos dos LEDs
GPIO.setmode(GPIO.BCM)
GPIO.setup(6, GPIO.OUT)  # LED verde (Acesso liberado)
GPIO.setup(5, GPIO.OUT)  # LED vermelho (Acesso negado)

# Inicializa os LEDs desligados
GPIO.output(6, GPIO.LOW)
GPIO.output(5, GPIO.LOW)

# Cria o objeto "leitor" para a instância "SimpleMFRC522" da biblioteca
leitor = SimpleMFRC522()

# Função para carregar os IDs e textos do arquivo CSV
def carregar_cadastro_csv():
    cadastro = {}
    try:
        with open('cadastro.csv', mode='r') as file:
            csv_reader = csv.reader(file)
            next(csv_reader)  # Pular o cabeçalho
            for row in csv_reader:
                id_csv = int(row[0])  # Converte a string do CSV para número
                texto_csv = row[1]
                cadastro[id_csv] = texto_csv
    except FileNotFoundError:
        print("Arquivo cadastro.csv não encontrado.")
    return cadastro

# Carregar cadastro do arquivo CSV
cadastro = carregar_cadastro_csv()

print("Aproxime a tag do leitor para leitura.")

while True:  # Loop infinito
    try:
        # Criar as variáveis "id" e "texto", e atribuí-las às leituras da tag pelo leitor
        try:
            id, texto = leitor.read()

        print(f"ID: {id}\nTexto: {texto}")  # Exibe as informações coletadas
        
        # Verifica se o ID lido está no cadastro
        if id in cadastro:
            print("Acesso liberado!")
            print(f"Bem-vindo, {cadastro[id]}")
            # Acende o LED verde (GPIO 5)
            GPIO.output(6, GPIO.HIGH)
            GPIO.output(5, GPIO.LOW)  # Garante que o LED vermelho está apagado
        else:
            print("Acesso negado!")
            # Acende o LED vermelho (GPIO 6)
            GPIO.output(5, GPIO.HIGH)
            GPIO.output(6, GPIO.LOW)  # Garante que o LED verde está apagado
        
        sleep(3)  # Aguarda 3 segundos para nova leitura
        
        # Desliga ambos os LEDs após o intervalo
        GPIO.output(6, GPIO.LOW)
        GPIO.output(5, GPIO.LOW)
    
    except Exception as e:
        print(f"Erro durante a leitura da tag: {str(e)}")
        GPIO.output(6, GPIO.HIGH)
        sleep(3)
        GPIO.output(6, GPIO.LOW)

    except KeyboardInterrupt:
        print("Programa encerrado.")
        GPIO.cleanup()
        break
