
def colour_8_to_16(colour: int)
    uint16_t r = (colour & 0b11100000) >> 3;
    uint16_t b = ((colour & 0b00011100) >> 2) * 9;
    uint16_t g = (colour & 0b0000011) * 10;
    return (r << 11) | (g << 5) | b;
}
