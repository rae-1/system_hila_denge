from PIL import Image

def extract_extra_bytes(png_file_path, offset, length, output_file_path):
    with open(png_file_path, 'rb') as file:
        file.seek(offset)  # Move to the specified offset
        extra_data = file.read(length)  # Read the extra data

    with open(output_file_path, 'wb') as output_file:
        output_file.write(extra_data)  # Write the extra data to a new file

# Usage
png_file_path = 'tech_council_logo.png'  # Path to your PNG image
offset = 0x47c0  # Hexadecimal offset where extra data starts
length = 271378  # Number of bytes of extra data
output_file_path = 'extra_data.bin'  # Path to save the extracted data

extract_extra_bytes(png_file_path, offset, length, output_file_path)
