import csv

# Function to convert CSV to PLY
def csv_to_ply(csv_filename, ply_filename):
    points = []
    
    # Read CSV data
    with open(csv_filename, mode='r') as csvfile:
        csvreader = csv.reader(csvfile)
        header = next(csvreader)  # Skip the header row
        for row in csvreader:
            points.append([float(coord) for coord in row])

    # Write PLY data
    with open(ply_filename, mode='w') as plyfile:
        plyfile.write("ply\n")
        plyfile.write("format ascii 1.0\n")
        plyfile.write(f"element vertex {len(points)}\n")
        plyfile.write("property float x\n")
        plyfile.write("property float y\n")
        plyfile.write("property float z\n")
        plyfile.write("end_header\n")
        
        for point in points:
            plyfile.write(f"{point[0]} {point[1]} {point[2]}\n")

# Example usage
csv_to_ply('./serial_data.csv', './uploads/output.ply')
#print("HElooooooo")