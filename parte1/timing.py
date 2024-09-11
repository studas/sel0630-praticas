import RPi.GPIO as GPIO
import time

LED_PIN = 18

GPIO.setmode(GPIO.BCM)
GPIO.setup(LED_PIN, GPIO.OUT)

def contagem_regressiva(tempo):
    # Realiza a contagem regressiva
    try:
        while tempo:
            GPIO.output(LED_PIN, GPIO.LOW)
            minutos, segundos = divmod(tempo, 60)
            print(f'{minutos:02d}:{segundos:02d}', end='\r')
            time.sleep(1)
            tempo -= 1
        print('00:00')  # Exibe o final da contagem
        GPIO.output(LED_PIN, GPIO.HIGH)
        print("A contagem terminou. O LED acendeu!")
    except KeyboardInterrupt:
        print("\nA contagem foi interrompida pelo usuário (Ctrl+C).")

def entrada_tempo():
    while True:
        try:
            tempo = int(input("Digite o tempo em segundos para a contagem regressiva: "))
            if tempo < 0:
                raise ValueError("O número deve ser positivo.")
            return tempo
        except ValueError as e:
            print(f"Entrada inválida: {e}. Tente novamente.")

def cleanup():
    while True:
        try:
            time.sleep(1/30)
            pass
        except KeyboardInterrupt:
            GPIO.cleanup()
            pass

def main():
    tempo = entrada_tempo()
    contagem_regressiva(tempo)
    cleanup()


if __name__ == "__main__":
    main()
