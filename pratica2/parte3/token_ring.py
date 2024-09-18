import threading
import time
import RPi.GPIO as GPIO
import signal
import sys

# GPIO setup
LED_PINS = [4, 17, 27, 22, 0, 11, 9, 10]  # Example GPIO pins for 8 LEDs
NUM_THREADS = len(LED_PINS)
mutex_array = [threading.Lock() for _ in range(NUM_THREADS)]
current_thread = 0

# Setup GPIO
GPIO.setmode(GPIO.BCM)
for pin in LED_PINS:
    GPIO.setup(pin, GPIO.OUT)
    GPIO.output(pin, GPIO.LOW)  # Ensure all LEDs are initially off

def signal_handler(sig, frame):
    """Handles Ctrl+C signal to exit the program gracefully."""
    print("Program exiting...")
    GPIO.cleanup()  # Cleanup GPIO settings
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

def led_token_ring(index):
    global current_thread
    while True:
        # Wait until it's this thread's turn to acquire the mutex
        mutex_array[index].acquire()
        
        # Critical section: Turn on the LED
        print(f"Thread {index} turning on LED {LED_PINS[index]}")
        GPIO.output(LED_PINS[index], GPIO.HIGH)
        time.sleep(0.5)
        GPIO.output(LED_PINS[index], GPIO.LOW)
        
        # Release the mutex and allow the next thread to proceed
        next_thread = (index + 1) % NUM_THREADS
        mutex_array[next_thread].release()

def main():
    # Initially lock all except the first mutex
    for i in range(1, NUM_THREADS):
        mutex_array[i].acquire()

    # Create and start the threads
    threads = []
    for i in range(NUM_THREADS):
        t = threading.Thread(target=led_token_ring, args=(i,))
        threads.append(t)
        t.start()

    # Join the threads (this program will run indefinitely until Ctrl+C is pressed)
    for t in threads:
        t.join()

if __name__ == "__main__":
    main()

