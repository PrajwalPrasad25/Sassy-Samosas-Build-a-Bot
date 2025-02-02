import serial
import time
import csv
import re
import chardet

def extract_floats(s):
    return [float(x) for x in re.findall(r"[-+]?\d*\.\d+|\d+", s)]

def csv_to_ply(csv_filename, ply_filename):
    points = []
    
    # Read CSV data
    with open(csv_filename, mode='r') as csvfile:
        csvreader = csv.reader(csvfile)
        header = next(csvreader)  # Skip the header row
        for row in csvreader:
            points.append([float(coord) for coord in row])

    # Write PLY data
    with open(ply_filename, mode='a') as plyfile:
        plyfile.write("ply\n")
        plyfile.write("format ascii 1.0\n")
        plyfile.write(f"element vertex {len(points)}\n")
        plyfile.write("property float x\n")
        plyfile.write("property float y\n")
        plyfile.write("property float z\n")
        plyfile.write("end_header\n")
        
        for point in points:
            plyfile.write(f"{point[0]} {point[1]} {point[2]}\n")

# Open the serial port (adjust port to match your setup)
ser = serial.Serial('/dev/cu.usbserial-0001', 115200)

def detect_encoding(byte_data):
    result = chardet.detect(byte_data)
    return result['encoding'] if result['encoding'] else 'utf-8'

# Open CSV file
with open("tof_data.csv", mode='w', encoding='utf-8', errors='replace') as file:
    with open("serial_data.csv", mode='w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        writer.writerow(["X", "Y", "Z"])  # Header row

        print(" Starting Serial Data Logging... Press CTRL+C to stop.")

        try:
            while True:
                if ser.in_waiting > 0:  # Check if data is available
                    raw_data = ser.readline().decode('utf-8', errors='replace').strip()  # Read & clean

                    # Extract floating point values
                    float_values = extract_floats(raw_data)

                    # Ensure at least 3 values exist before writing
                    if len(float_values) >= 3:
                        x, y, z = float_values[:3]  # Take first three values
                        writer.writerow([x, y, z])  # Write to CSV
                        print(f"Logged: X={x}, Y={y}, Z={z}")  # Show in console
                    else:
                        print(f"Skipping invalid data: {raw_data}")
                    # csv_to_ply('tof_data.csv', 'output.ply')

        except KeyboardInterrupt:
            print("\n Data logging stopped.")
            ser.close()  # Close serial port
   