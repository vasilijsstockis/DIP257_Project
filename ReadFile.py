import serial
import time

# --- CONFIGURE SERIAL PORT ---
arduino_port = "COM3"  # replace with your Arduino COM port
baud_rate = 9600
file_path = "Comand2.txt"  # file containing lines to send

# Open serial connection
ser = serial.Serial(arduino_port, baud_rate, timeout=1)
time.sleep(2) 

with open(file_path, 'r') as f:
    data = f.read()

ser.write(data.encode())

while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode().strip()
        print(line)
