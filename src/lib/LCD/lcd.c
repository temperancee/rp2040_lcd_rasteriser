/*****************************************************************************
* | File      	:   lcd.c
* | Author      :   Waveshare team, edited by temperancee
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master
*                and enhance portability
******************************************************************************/
#include "lcd.h"
#include "PWM.h"
#include "SPI.h"
#include "STDIO.h"
#include "GPIO.h"
#include "Delay.h"

#include <stdint.h>
#include "hardware/dma.h"

LCD_1IN28_ATTRIBUTES LCD_1IN28;


/******************************************************************************
function :	Hardware reset
parameter:
******************************************************************************/
static void LCD_1IN28_Reset(void)
{
    GPIO_Write(LCD_RST_PIN, 1);
    Delay_ms(100);
    GPIO_Write(LCD_RST_PIN, 0);
    Delay_ms(100);
    GPIO_Write(LCD_RST_PIN, 1);
    // Set CS low forever since the LCD is the only SPI slave 
    GPIO_Write(LCD_CS_PIN, 0);
    Delay_ms(100);
}

/******************************************************************************
function :	send command
parameter:
     Reg : Command register
******************************************************************************/
static void LCD_1IN28_SendCommand(uint8_t Reg)
{
    GPIO_Write(LCD_DC_PIN, 0);
    SPI_Write_Byte(LCD_SPI_PORT, Reg);
}

/******************************************************************************
function :	send data
parameter:
    Data : Write data
******************************************************************************/
static void LCD_1IN28_SendData_8Bit(uint8_t Data)
{
    GPIO_Write(LCD_DC_PIN, 1);
    SPI_Write_Byte(LCD_SPI_PORT, Data);
}

/******************************************************************************
function :	send data
parameter:
    Data : Write data
******************************************************************************/
static void LCD_1IN28_SendData_16Bit(uint16_t Data)
{
    GPIO_Write(LCD_DC_PIN, 1);
    SPI_Write_Byte(LCD_SPI_PORT, Data >> 8);
    SPI_Write_Byte(LCD_SPI_PORT, Data);
}

/******************************************************************************
function :	Initialize the lcd register
parameter:
******************************************************************************/
static void LCD_1IN28_InitReg(void)
{
    LCD_1IN28_SendCommand(INTER_REG_ENABLE2);
    // Most of these registers aren't documented in the data sheet,
    // so I have no idea what they do, nor if some can be removed
    LCD_1IN28_SendCommand(0xEB);
    LCD_1IN28_SendData_8Bit(0x14);

    LCD_1IN28_SendCommand(INTER_REG_ENABLE1);
    LCD_1IN28_SendCommand(INTER_REG_ENABLE2);

    LCD_1IN28_SendCommand(0xEB);
    LCD_1IN28_SendData_8Bit(0x14);

    LCD_1IN28_SendCommand(0x84);
    LCD_1IN28_SendData_8Bit(0x40);

    LCD_1IN28_SendCommand(0x85);
    LCD_1IN28_SendData_8Bit(0xFF);

    LCD_1IN28_SendCommand(0x86);
    LCD_1IN28_SendData_8Bit(0xFF);

    LCD_1IN28_SendCommand(0x87);
    LCD_1IN28_SendData_8Bit(0xFF);

    LCD_1IN28_SendCommand(0x88);
    LCD_1IN28_SendData_8Bit(0x0A);

    LCD_1IN28_SendCommand(0x89);
    LCD_1IN28_SendData_8Bit(0x21);

    LCD_1IN28_SendCommand(0x8A);			
    LCD_1IN28_SendData_8Bit(0x00); 

    LCD_1IN28_SendCommand(0x8B);			
    LCD_1IN28_SendData_8Bit(0x80); 

    LCD_1IN28_SendCommand(0x8C);			
    LCD_1IN28_SendData_8Bit(0x01); 

    LCD_1IN28_SendCommand(0x8D);			
    LCD_1IN28_SendData_8Bit(0x01); 

    LCD_1IN28_SendCommand(0x8E);			
    LCD_1IN28_SendData_8Bit(0xFF); 

    LCD_1IN28_SendCommand(0x8F);			
    LCD_1IN28_SendData_8Bit(0xFF); 


    LCD_1IN28_SendCommand(0xB6);
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(0x20);

    // BUG: The manufacturer added comment here says "Set as vertical
    // screen", but this command is MEMORY_ACCESS_CTRL, and setting
    // 0x08 means the driver expects colours to be passed in "BGR" 
    // order, rather than RGB
    LCD_1IN28_SendCommand(0x36);
    LCD_1IN28_SendData_8Bit(0x08);//Set as vertical screen

    // Sets the colour depth
    // I thought this command did nothing, but it actually breaks
    // everything if set incorrectly
    LCD_1IN28_SendCommand(COLMOD);			
    LCD_1IN28_SendData_8Bit(0x05); // 0x03 for 12 bit colour depth. 0x05 for 16 bit 


    LCD_1IN28_SendCommand(0x90);			
    LCD_1IN28_SendData_8Bit(0x08);
    LCD_1IN28_SendData_8Bit(0x08);
    LCD_1IN28_SendData_8Bit(0x08);
    LCD_1IN28_SendData_8Bit(0x08); 

    LCD_1IN28_SendCommand(0xBD);			
    LCD_1IN28_SendData_8Bit(0x06);
    
    LCD_1IN28_SendCommand(0xBC);			
    LCD_1IN28_SendData_8Bit(0x00);	

    LCD_1IN28_SendCommand(0xFF);			
    LCD_1IN28_SendData_8Bit(0x60);
    LCD_1IN28_SendData_8Bit(0x01);
    LCD_1IN28_SendData_8Bit(0x04);

    LCD_1IN28_SendCommand(0xC3);			
    LCD_1IN28_SendData_8Bit(0x13);
    LCD_1IN28_SendCommand(0xC4);			
    LCD_1IN28_SendData_8Bit(0x13);

    LCD_1IN28_SendCommand(0xC9);			
    LCD_1IN28_SendData_8Bit(0x22);

    LCD_1IN28_SendCommand(0xBE);			
    LCD_1IN28_SendData_8Bit(0x11); 

    LCD_1IN28_SendCommand(0xE1);			
    LCD_1IN28_SendData_8Bit(0x10);
    LCD_1IN28_SendData_8Bit(0x0E);

    LCD_1IN28_SendCommand(0xDF);			
    LCD_1IN28_SendData_8Bit(0x21);
    LCD_1IN28_SendData_8Bit(0x0c);
    LCD_1IN28_SendData_8Bit(0x02);

    LCD_1IN28_SendCommand(0xF0);   
    LCD_1IN28_SendData_8Bit(0x45);
    LCD_1IN28_SendData_8Bit(0x09);
    LCD_1IN28_SendData_8Bit(0x08);
    LCD_1IN28_SendData_8Bit(0x08);
    LCD_1IN28_SendData_8Bit(0x26);
    LCD_1IN28_SendData_8Bit(0x2A);

    LCD_1IN28_SendCommand(0xF1);    
    LCD_1IN28_SendData_8Bit(0x43);
    LCD_1IN28_SendData_8Bit(0x70);
    LCD_1IN28_SendData_8Bit(0x72);
    LCD_1IN28_SendData_8Bit(0x36);
    LCD_1IN28_SendData_8Bit(0x37);  
    LCD_1IN28_SendData_8Bit(0x6F);


    LCD_1IN28_SendCommand(0xF2);   
    LCD_1IN28_SendData_8Bit(0x45);
    LCD_1IN28_SendData_8Bit(0x09);
    LCD_1IN28_SendData_8Bit(0x08);
    LCD_1IN28_SendData_8Bit(0x08);
    LCD_1IN28_SendData_8Bit(0x26);
    LCD_1IN28_SendData_8Bit(0x2A);

    LCD_1IN28_SendCommand(0xF3);   
    LCD_1IN28_SendData_8Bit(0x43);
    LCD_1IN28_SendData_8Bit(0x70);
    LCD_1IN28_SendData_8Bit(0x72);
    LCD_1IN28_SendData_8Bit(0x36);
    LCD_1IN28_SendData_8Bit(0x37); 
    LCD_1IN28_SendData_8Bit(0x6F);

    LCD_1IN28_SendCommand(0xED);	
    LCD_1IN28_SendData_8Bit(0x1B); 
    LCD_1IN28_SendData_8Bit(0x0B); 

    LCD_1IN28_SendCommand(0xAE);			
    LCD_1IN28_SendData_8Bit(0x77);
    
    LCD_1IN28_SendCommand(0xCD);			
    LCD_1IN28_SendData_8Bit(0x63);		


    LCD_1IN28_SendCommand(0x70);			
    LCD_1IN28_SendData_8Bit(0x07);
    LCD_1IN28_SendData_8Bit(0x07);
    LCD_1IN28_SendData_8Bit(0x04);
    LCD_1IN28_SendData_8Bit(0x0E); 
    LCD_1IN28_SendData_8Bit(0x0F); 
    LCD_1IN28_SendData_8Bit(0x09);
    LCD_1IN28_SendData_8Bit(0x07);
    LCD_1IN28_SendData_8Bit(0x08);
    LCD_1IN28_SendData_8Bit(0x03);

    LCD_1IN28_SendCommand(0xE8);			
    LCD_1IN28_SendData_8Bit(0x34);

    LCD_1IN28_SendCommand(0x62);			
    LCD_1IN28_SendData_8Bit(0x18);
    LCD_1IN28_SendData_8Bit(0x0D);
    LCD_1IN28_SendData_8Bit(0x71);
    LCD_1IN28_SendData_8Bit(0xED);
    LCD_1IN28_SendData_8Bit(0x70); 
    LCD_1IN28_SendData_8Bit(0x70);
    LCD_1IN28_SendData_8Bit(0x18);
    LCD_1IN28_SendData_8Bit(0x0F);
    LCD_1IN28_SendData_8Bit(0x71);
    LCD_1IN28_SendData_8Bit(INTER_REG_ENABLE2);
    LCD_1IN28_SendData_8Bit(0x70); 
    LCD_1IN28_SendData_8Bit(0x70);

    LCD_1IN28_SendCommand(0x63);			
    LCD_1IN28_SendData_8Bit(0x18);
    LCD_1IN28_SendData_8Bit(0x11);
    LCD_1IN28_SendData_8Bit(0x71);
    LCD_1IN28_SendData_8Bit(0xF1);
    LCD_1IN28_SendData_8Bit(0x70); 
    LCD_1IN28_SendData_8Bit(0x70);
    LCD_1IN28_SendData_8Bit(0x18);
    LCD_1IN28_SendData_8Bit(0x13);
    LCD_1IN28_SendData_8Bit(0x71);
    LCD_1IN28_SendData_8Bit(0xF3);
    LCD_1IN28_SendData_8Bit(0x70); 
    LCD_1IN28_SendData_8Bit(0x70);

    LCD_1IN28_SendCommand(0x64);			
    LCD_1IN28_SendData_8Bit(0x28);
    LCD_1IN28_SendData_8Bit(0x29);
    LCD_1IN28_SendData_8Bit(0xF1);
    LCD_1IN28_SendData_8Bit(0x01);
    LCD_1IN28_SendData_8Bit(0xF1);
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(0x07);

    LCD_1IN28_SendCommand(0x66);			
    LCD_1IN28_SendData_8Bit(0x3C);
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(0xCD);
    LCD_1IN28_SendData_8Bit(0x67);
    LCD_1IN28_SendData_8Bit(0x45);
    LCD_1IN28_SendData_8Bit(0x45);
    LCD_1IN28_SendData_8Bit(0x10);
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(0x00);

    LCD_1IN28_SendCommand(0x67);			
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(0x3C);
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(0x01);
    LCD_1IN28_SendData_8Bit(0x54);
    LCD_1IN28_SendData_8Bit(0x10);
    LCD_1IN28_SendData_8Bit(0x32);
    LCD_1IN28_SendData_8Bit(0x98);

    LCD_1IN28_SendCommand(0x74);			
    LCD_1IN28_SendData_8Bit(0x10);	
    LCD_1IN28_SendData_8Bit(0x85);	
    LCD_1IN28_SendData_8Bit(0x80);
    LCD_1IN28_SendData_8Bit(0x00); 
    LCD_1IN28_SendData_8Bit(0x00); 
    LCD_1IN28_SendData_8Bit(0x4E);
    LCD_1IN28_SendData_8Bit(0x00);					
    
    LCD_1IN28_SendCommand(0x98);			
    LCD_1IN28_SendData_8Bit(0x3e);
    LCD_1IN28_SendData_8Bit(0x07);

    LCD_1IN28_SendCommand(0x35);	
    LCD_1IN28_SendCommand(0x21);

    LCD_1IN28_SendCommand(0x11);
    Delay_ms(120);
    LCD_1IN28_SendCommand(0x29);
    Delay_ms(20);
}

/********************************************************************************
function:	Set the resolution and scanning method of the screen
parameter:
		Scan_dir:   Scan direction
********************************************************************************/
static void LCD_1IN28_SetAttributes(uint8_t Scan_dir)
{
    //Get the screen scan direction
    LCD_1IN28.SCAN_DIR = Scan_dir;
    uint8_t MemoryAccessReg = 0x08;

    //Get GRAM and LCD width and height
    if(Scan_dir == HORIZONTAL) {
        LCD_1IN28.HEIGHT = LCD_1IN28_HEIGHT;
        LCD_1IN28.WIDTH = LCD_1IN28_WIDTH;
        MemoryAccessReg = 0Xc8;
    } else {
        LCD_1IN28.HEIGHT = LCD_1IN28_WIDTH;
        LCD_1IN28.WIDTH = LCD_1IN28_HEIGHT;
        MemoryAccessReg = 0X68;
    }

    // Set the read / write scan direction of the frame memory
    LCD_1IN28_SendCommand(0x36); //MX, MY, RGB mode
    //LCD_1IN28_SendData_8Bit(MemoryAccessReg);	//0x08 set RGB
    LCD_1IN28_SendData_8Bit(MemoryAccessReg);	//0x08 set RGB
}

/**
 * @brief Initialise the LCD
 * @param scan_dir - scan direction, HORIZONTAL is standard
 * @param brightness - Screen brightness - a value between 0-100
 */
void LCD_1IN28_Init(uint8_t scan_dir, uint8_t brightness)
{

    STDIO_INIT_ALL();

    /* GPIO Initialisation */
    GPIO_Mode(LCD_RST_PIN, GPIO_MODE_OUT);
    GPIO_Mode(LCD_DC_PIN, GPIO_MODE_OUT);
    GPIO_Mode(LCD_CS_PIN, GPIO_MODE_OUT);
    GPIO_Mode(LCD_BL_PIN, GPIO_MODE_OUT);
    // Set CS high (so no peripheral selected for writing/reading)
    // GPIO_Write(LCD_CS_PIN, 1);
    // Set DC=0, so LCD in command mode
    GPIO_Write(LCD_DC_PIN, 0);
    // Set BL=1. This sets LEDK=0, I think, so in the
    // language of the LCD's datasheet, BC=0, and the display has
    // no light
    GPIO_Write(LCD_BL_PIN, 1);


    /* PWM Initialisation */
    GPIO_Set_Function(LCD_BL_PIN, GPIO_FUNCTION_PWM);
    uint32_t slice_num = PWM_GPIO_to_Slice_Num(LCD_BL_PIN);
    PWM_Set_Wrap(slice_num, 100);
    PWM_Set_Chan_Level(slice_num, PWM_CHANNEL_B, 0);
    PWM_Set_Clkdiv(slice_num, 50);
    PWM_Set_Enabled(slice_num, true);
    
    /* SPI Initialisation */
    SPI_Init(LCD_SPI_PORT, 40000 * 1000);
    GPIO_Set_Function(LCD_CLK_PIN, GPIO_FUNCTION_SPI);
    GPIO_Set_Function(LCD_MOSI_PIN, GPIO_FUNCTION_SPI);

    /* Reset and configure registers */
    //Hardware reset
    LCD_1IN28_Reset();

    //Set the resolution and scanning method of the screen
    LCD_1IN28_SetAttributes(scan_dir);
    
    // Initialises register values
    LCD_1IN28_InitReg();

    /* Turn on the backlight at 50% brightness */
    PWM_Set_Chan_Level(slice_num, PWM_CHANNEL_B, brightness);
}

/********************************************************************************
function:	Sets the start position and size of the display area
parameter:
		Xstart 	:   X direction Start coordinates
		Ystart  :   Y direction Start coordinates
		Xend    :   X direction end coordinates
		Yend    :   Y direction end coordinates
********************************************************************************/
void LCD_1IN28_SetWindows(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend)
{
    //set the X coordinates
    LCD_1IN28_SendCommand(0x2A);
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(Xstart);
    LCD_1IN28_SendData_8Bit((Xend-1)>>8);
    LCD_1IN28_SendData_8Bit(Xend-1);

    //set the Y coordinates
    LCD_1IN28_SendCommand(0x2B);
    LCD_1IN28_SendData_8Bit(0x00);
    LCD_1IN28_SendData_8Bit(Ystart);
    LCD_1IN28_SendData_8Bit((Xend-1)>>8);
    LCD_1IN28_SendData_8Bit(Yend-1);

    LCD_1IN28_SendCommand(0X2C);
}

/******************************************************************************
function :	Clear screen
parameter:
******************************************************************************/
void LCD_1IN28_Clear(uint16_t Color)
{
    uint16_t j;
    uint16_t row[LCD_1IN28_WIDTH];

    Color = ((Color<<8)&0xff00)|(Color>>8);

    for (j = 0; j < LCD_1IN28_WIDTH; j++) {
        row[j] = Color;
    }

    // WARNING: This function still uses 16 bit colour, and sends
    // framebuffers via CPU controlled SPI

    LCD_1IN28_SetWindows(0, 0, LCD_1IN28_WIDTH, LCD_1IN28_HEIGHT);
    GPIO_Write(LCD_DC_PIN, 1);
    for(int j = 0; j < LCD_1IN28_HEIGHT; j++) {
        SPI_Write_n_Bytes(LCD_SPI_PORT, (uint8_t *)row, LCD_1IN28_WIDTH*2);
    }
}

/******************************************************************************
function :	Sends the image buffer in RAM to display
parameter:
******************************************************************************/
void LCD_1IN28_Display(uint8_t *Image)
{

    LCD_1IN28_SetWindows(0, 0, LCD_1IN28_WIDTH, LCD_1IN28_HEIGHT);
    GPIO_Write(LCD_DC_PIN, 1);

    // DMA Config 
    // By default, the read address increments after each transfer
    // Our transfer size is 16 bits per transfer, so that makes 240*240*3/2 transfers
    
    const uint32_t transfer_count = 57600;
    const uint32_t dma_chan = dma_claim_unused_channel(true);
    dma_channel_config c = dma_channel_get_default_config(dma_chan);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_8); // The SPI registers are 16 bits on the RP2040
    channel_config_set_dreq(&c, spi_get_dreq(spi1, true));
    dma_channel_configure(
        dma_chan,
        &c,
        &spi_get_hw(spi1)->dr, // write address - not certain of what spi_get_hw does - it seems to simply return a pointer to the passed SPI instance if it's hardware spi, and do nothing if not
        Image, // read address
        dma_encode_transfer_count(transfer_count), // element count
        true  //  start transfer immediately
    );

    // Wait for it to finish
    dma_channel_wait_for_finish_blocking(dma_chan);
    while (spi_is_busy(spi1)) {
        tight_loop_contents();
    }

}

// void LCD_1IN28_DisplayWindows(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t *Image)
// {
//     // display
//     uint32_t Addr = 0;
//
//     uint16_t j;
//     LCD_1IN28_SetWindows(Xstart, Ystart, Xend , Yend);
//     GPIO_Write(LCD_DC_PIN, 1);;
//     for (j = Ystart; j < Yend; j++) {
//         Addr = Xstart + j * LCD_1IN28_WIDTH ;
//         SPI_Write_n_Bytes(LCD_SPI_PORT,(uint8_t *)&Image[Addr], (Xend-Xstart)*2);
//     }
// }

void LCD_1IN28_DisplayPoint(uint16_t X, uint16_t Y, uint16_t Color)
{
    LCD_1IN28_SetWindows(X,Y,X,Y);
    LCD_1IN28_SendData_16Bit(Color);
}
