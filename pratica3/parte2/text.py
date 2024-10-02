# Para descobrir qual a codificação da Tag com texto gravado anteriormente
from mfrc522 import SimpleMFRC522
from time import sleep
import RPi.GPIO as GPIO
#desabilitar os avisos
GPIO.setwarnings(False)
#cria o objeto "leitor" para a instância "SimpleMFRC522" da biblioteca
leitor = SimpleMFRC522()
print("Aproxime a tag do leitor para leitura.")
while True: #loop
#cria as variáveis "id" e "texto", e as atribui as leituras da id e do texto coletado
da tag pelo leitor, respectivamente
id,texto = leitor.read()
print("ID: {}\nTexto: {}".format(id, texto)) #exibe as informações coletadas
sleep(3) #aguarda 3 segundos para nova leitura
