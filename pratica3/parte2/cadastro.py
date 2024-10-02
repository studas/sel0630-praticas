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

        try:
            tag_id, _ = reader.read()
        except Exception as e:
            print(f"An error occurred while reading the tag: {e}")
            return
        
        print(f"Tag detected with ID: {tag_id}")
        
        # Optionally, write the user ID to the tag (uncomment if needed)
        reader.write(user_id)
        print(f"User ID \"{user_id}\" written to the tag successfully.")

        #check if the tag was successfully written
        print("Reading the tag to verify the written data...")
        read_user_id = reader.read_id()
        if read_user_id == user_id:
            print("Data verification successful!")
        else:
            print("Data verification failed. Please try again.")
            return
        
        #if the file does not exist, it will be created
        with open(csv_filename, mode='a', newline='') as csvfile:
            csv_writer = csv.writer(csvfile)
            csv_writer.writerow(['rfid_tag', 'user_id'])

        # Write the tag ID and user ID to the CSV file
        with open(csv_filename, mode='a', newline='') as csvfile:
            csv_writer = csv.writer(csvfile)
            csv_writer.writerow([tag_id, user_id])
        
        print(f"Registration successful! Tag ID {tag_id} associated with User ID {user_id}.")

    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        GPIO.cleanup()

if __name__ == "__main__":
    try:
        while True:
            register_user()
            time.sleep(1)
    except KeyboardInterrupt:
        print("\nExiting program.")
    finally:
        GPIO.cleanup()

