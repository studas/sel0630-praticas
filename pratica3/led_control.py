import smbus
import sys
import time

# I2C configuration
I2C_BUS_NUMBER = 1  # Typically 1 for Raspberry Pi
I2C_ADDRESS = 0x09   # Must match the Arduino's I2C address

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 control_led.py [0|1]")
        sys.exit(1)

    command = sys.argv[1]
    if command not in ['0', '1']:
        print("Invalid command. Use '0' to turn OFF or '1' to turn ON the LED.")
        sys.exit(1)

    # Initialize I2C (SMBus)
    bus = smbus.SMBus(I2C_BUS_NUMBER)

    try:
        # Send the command as a byte
        bus.write_byte(I2C_ADDRESS, ord(command))
        print(f"Sent command '{command}' to Arduino.")
    except Exception as e:
        print(f"Error communicating with Arduino: {e}")

    bus.close()

if __name__ == "__main__":
    main()
