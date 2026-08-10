import os

def colour_8_to_16(colour: int):
    r = (colour & 0b11100000) >> 3;
    b = ((colour & 0b00011100) >> 2) * 9;
    g = (colour & 0b0000011) * 10;
    return (r << 11) | (g << 5) | b;

def generate_cols():
    cols = ""
    for i in range(255):
        cols += f"    {hex(colour_8_to_16(i))},\n"
    cols += f"    {hex(colour_8_to_16(255))}"
    return cols

string = f"""
static const uint16_t col_lut[256] = {{
    {generate_cols()}
}}
"""

if not os.path.exists("src/lib/LCD/colour_table.h"):
    with open ("src/lib/LCD/colour_table.h", "w") as f:
        f.write(string)
