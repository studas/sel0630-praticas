import smbus
import time

I2C_BUS_NUMBER = 1
I2C_ADDRESS = 0x09

def read_potentiometer(bus, address):
    try:
        data = bus.read_i2c_block_data(address, 0, 2)
        
        pot_value = (data[0] << 8) | data[1]
        
        return pot_value
    except Exception as e:
        print(f"Error reading from I2C device: {e}")
        return None

def main():
    bus = smbus.SMBus(I2C_BUS_NUMBER)
    
    try:
        while True:
            pot_raw_value = read_potentiometer(bus, I2C_ADDRESS)
            pot_value = (20/1023)*pot_raw_value
            if pot_raw_value is not None:
                print(f"Potentiometer Value: {pot_value:.2f} k Ohm")
            else:
                print("Failed to read potentiometer value.")
            
            time.sleep(1)  # Wait for 1 second before the next read
    except KeyboardInterrupt:
        print("\nExiting program.")
    finally:
        bus.close()

if __name__ == "__main__":
    main()
