import RPi.GPIO as GPIO
from mfrc522 import SimpleMFRC522
import csv
import time

def register_user(csv_filename='cadastro.csv'):
    # Initialize the RFID reader
    reader = SimpleMFRC522()
    
    try:
        user_id = input("Enter the User ID: ").strip()
        
        if not user_id:
            print("User ID cannot be empty.")
            return
        
        print("Please place the RFID tag near the reader...")
        
        # Wait for a tag and read its ID
        tag_id, _ = reader.read()
        
        print(f"Tag detected with ID: {tag_id}")
        
        # Optionally, write the user ID to the tag (uncomment if needed)
        reader.write(user_id)
        print(f"User ID \"{user_id}\" written to the tag successfully.")
        
        # Write the tag ID and user ID to the CSV file
        with open(csv_filename, mode='a', newline='') as csvfile:
            csv_writer = csv.writer(csvfile)
            csv_writer.writerow([tag_id, user_id])
        
        print(f"Registration successful! Tag ID {tag_id} associated with User ID {user_id}.")

    except KeyboardInterrupt:
        print("\nOperation cancelled by user.")
    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        GPIO.cleanup()

if __name__ == "__main__":
    while True:
        register_user()
        time.sleep(1)

