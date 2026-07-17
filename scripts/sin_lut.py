from math import sin, pi
import os

def generate_sins():
    sins = ""
    for i in range(180):
        sins += f"    FLOAT_TO_Q16({sin(i/2 * pi/180)})"
        if i != 179:
            sins += "\n"
    return sins


string = f"""
static const q16 sin_lut[180] = {{
{generate_sins()}
}};
"""

if not os.path.exists("../lib/Rasteriser/types/angles.h"):
    with open ("../lib/Rasteriser/types/angles.h", "w") as f:
        f.write(string)

