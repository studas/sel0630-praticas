import time

def contagem_regressiva(tempo):
    # Realiza a contagem regressiva
    try:
        while tempo:
            minutos, segundos = divmod(tempo, 60)
            print(f'{minutos:02d}:{segundos:02d}', end='\r')
            time.sleep(1)
            tempo -= 1
        print('00:00')  # Exibe o final da contagem
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

def main():
    tempo = entrada_tempo()
    contagem_regressiva(tempo)

if __name__ == "__main__":
    main()
