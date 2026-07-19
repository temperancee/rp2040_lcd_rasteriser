#include "GUI_Paint.h"
#include "Debug.h"
#include <stdint.h>

PAINT Paint;

/******************************************************************************
function: Create Image
parameter:
    image   :   Pointer to the image cache
    width   :   The width of the picture
    Height  :   The height of the picture
    Rotate  :   ??
    Color   :   Whether the picture is inverted
******************************************************************************/
void Paint_NewImage(uint8_t *image, uint16_t Width, uint16_t Height, uint16_t Colour)
{
    Paint.Image = NULL;
    Paint.Image = image;

    Paint.Width = Width;
    Paint.Height = Height;
    Paint.Colour = Colour;    

    Paint.WidthByte = Paint.Width*2; 
    Paint.HeightByte = Height;    
}

/******************************************************************************
function: Select Image
parameter:
    image : Pointer to the image cache
******************************************************************************/
void Paint_SelectImage(uint8_t *image)
{
    Paint.Image = image;
}

/******************************************************************************
function: Draw Pixels
parameter:
    Xpoint : At point X
    Ypoint : At point Y
    Color  : Painted colors
******************************************************************************/
void Paint_SetPixel(uint16_t Xpoint, uint16_t Ypoint, uint16_t Colour)
{
    if(Xpoint > Paint.Width || Ypoint > Paint.Height){
        Debug("Exceeding display boundaries\r\n");
        return;
    }      

    uint32_t Addr = Xpoint*2 + Ypoint*Paint.WidthByte;
    // These bit masks truncate the color from 16 bit to 8 bit
    Paint.Image[Addr] = 0xff & (Colour>>8);
    Paint.Image[Addr+1] = 0xff & Colour;

}

/******************************************************************************
function: Clear the color of the picture
parameter:
    Color : Painted colors
******************************************************************************/
void Paint_Clear(uint16_t Colour)
{
    for (uint16_t Y = 0; Y < Paint.HeightByte; Y++) {
        for (uint16_t X = 0; X < Paint.Width; X++ ) {
            uint32_t Addr = X*2 + Y*Paint.WidthByte;
            // These bit masks may appear pointless, but they
            // truncate the color from 16 bit to 8 bit
            Paint.Image[Addr] = 0xff & (Colour>>8);
            Paint.Image[Addr+1] = 0xff & Colour;
        }
    }
}
