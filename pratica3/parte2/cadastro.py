import RPi.GPIO as GPIO
from mfrc522 import SimpleMFRC522
import csv
import time
import sys
import os

def register_user(user_id, csv_filename='cadastro.csv'):
    reader = SimpleMFRC522()

    try:
        if not user_id:
            print("Error: User ID cannot be empty.")
            sys.exit(1)

        print(f"Registering User ID: {user_id}")
        print("Please place the RFID tag near the reader...")

        try:
            tag_id, _ = reader.read()
            print(f"Tag detected with ID: {tag_id}")
        except Exception as e:
            print(f"Error reading the tag: {e}")
            sys.exit(1)

        # Write the user ID to the RFID tag
        try:
            reader.write(user_id)
            print(f"User ID '{user_id}' written to the tag successfully.")
        except Exception as e:
            print(f"Error writing to the tag: {e}")
            sys.exit(1)

        # Verify the written data
        time.sleep(1)  # Short delay to ensure data is written
        try:
            _, read_user_id = reader.read()
            if read_user_id.strip() == user_id:
                print("Data verification successful!")
            else:
                print("Data verification failed. Please try again.")
                sys.exit(1)
        except Exception as e:
            print(f"Error verifying the tag data: {e}")
            sys.exit(1)

        # Ensure the CSV file has headers
        file_exists = os.path.isfile(csv_filename)
        try:
            with open(csv_filename, mode='a', newline='') as csvfile:
                csv_writer = csv.writer(csvfile)
                if not file_exists:
                    csv_writer.writerow(["Tag ID", "User ID"])  # Write header if file doesn't exist
                csv_writer.writerow([tag_id, user_id])
            print(f"Registration successful! Tag ID {tag_id} associated with User ID {user_id}.")
        except Exception as e:
            print(f"Error writing to CSV file: {e}")
            sys.exit(1)

    finally:
        GPIO.cleanup()

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 cadastro.py <user_id>")
        sys.exit(1)
    
    user_id = sys.argv[1].strip()
    register_user(user_id)

if __name__ == "__main__":
    main()
