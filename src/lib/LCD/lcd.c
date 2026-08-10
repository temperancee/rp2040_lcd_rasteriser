#include "lcd.h"

#include "PWM.h"
#include "SPI.h"
#include "GPIO.h"
#include "Delay.h"

#include <stdint.h>

LCD_1IN28_ATTRIBUTES LCD_1IN28;


/******************************************************************************
function :	Hardware reset
parameter:
******************************************************************************/
static void lcd_reset(void)
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
static void lcd_send_command(uint8_t Reg)
{
    GPIO_Write(LCD_DC_PIN, 0);
    SPI_Write_Byte(LCD_SPI_PORT, Reg);
}

/******************************************************************************
function :	send data
parameter:
    Data : Write data
******************************************************************************/
static void lcd_send_data_8bit(uint8_t Data)
{
    GPIO_Write(LCD_DC_PIN, 1);
    SPI_Write_Byte(LCD_SPI_PORT, Data);
}

/******************************************************************************
function :	send data
parameter:
    Data : Write data
******************************************************************************/
static void lcd_send_data_16bit(uint16_t Data)
{
    GPIO_Write(LCD_DC_PIN, 1);
    SPI_Write_Byte(LCD_SPI_PORT, Data >> 8);
    SPI_Write_Byte(LCD_SPI_PORT, Data);
}

/******************************************************************************
function :	Initialize the lcd register
parameter:
******************************************************************************/
static void lcd_init_regs(void)
{
    lcd_send_command(INTER_REG_ENABLE2);
    // Most of these registers aren't documented in the data sheet,
    // so I have no idea what they do, nor if some can be removed
    lcd_send_command(0xEB);
    lcd_send_data_8bit(0x14);

    lcd_send_command(INTER_REG_ENABLE1);
    lcd_send_command(INTER_REG_ENABLE2);

    lcd_send_command(0xEB);
    lcd_send_data_8bit(0x14);

    lcd_send_command(0x84);
    lcd_send_data_8bit(0x40);

    lcd_send_command(0x85);
    lcd_send_data_8bit(0xFF);

    lcd_send_command(0x86);
    lcd_send_data_8bit(0xFF);

    lcd_send_command(0x87);
    lcd_send_data_8bit(0xFF);

    lcd_send_command(0x88);
    lcd_send_data_8bit(0x0A);

    lcd_send_command(0x89);
    lcd_send_data_8bit(0x21);

    lcd_send_command(0x8A);			
    lcd_send_data_8bit(0x00); 

    lcd_send_command(0x8B);			
    lcd_send_data_8bit(0x80); 

    lcd_send_command(0x8C);			
    lcd_send_data_8bit(0x01); 

    lcd_send_command(0x8D);			
    lcd_send_data_8bit(0x01); 

    lcd_send_command(0x8E);			
    lcd_send_data_8bit(0xFF); 

    lcd_send_command(0x8F);			
    lcd_send_data_8bit(0xFF); 


    lcd_send_command(0xB6);
    lcd_send_data_8bit(0x00);
    lcd_send_data_8bit(0x20);

    // BUG: The manufacturer added comment here says "Set as vertical
    // screen", but this command is MEMORY_ACCESS_CTRL, and setting
    // 0x08 means the driver expects colours to be passed in "BGR" 
    // order, rather than RGB
    lcd_send_command(0x36);
    lcd_send_data_8bit(0x08);//Set as vertical screen

    // Sets the colour depth
    // I thought this command did nothing, but it actually breaks
    // everything if set incorrectly
    lcd_send_command(COLMOD);			
    lcd_send_data_8bit(0x05); // 0x05 for 16 bit colour depth (any other value causes an error)


    lcd_send_command(0x90);			
    lcd_send_data_8bit(0x08);
    lcd_send_data_8bit(0x08);
    lcd_send_data_8bit(0x08);
    lcd_send_data_8bit(0x08); 

    lcd_send_command(0xBD);			
    lcd_send_data_8bit(0x06);
    
    lcd_send_command(0xBC);			
    lcd_send_data_8bit(0x00);	

    lcd_send_command(0xFF);			
    lcd_send_data_8bit(0x60);
    lcd_send_data_8bit(0x01);
    lcd_send_data_8bit(0x04);

    lcd_send_command(0xC3);			
    lcd_send_data_8bit(0x13);
    lcd_send_command(0xC4);			
    lcd_send_data_8bit(0x13);

    lcd_send_command(0xC9);			
    lcd_send_data_8bit(0x22);

    lcd_send_command(0xBE);			
    lcd_send_data_8bit(0x11); 

    lcd_send_command(0xE1);			
    lcd_send_data_8bit(0x10);
    lcd_send_data_8bit(0x0E);

    lcd_send_command(0xDF);			
    lcd_send_data_8bit(0x21);
    lcd_send_data_8bit(0x0c);
    lcd_send_data_8bit(0x02);

    lcd_send_command(0xF0);   
    lcd_send_data_8bit(0x45);
    lcd_send_data_8bit(0x09);
    lcd_send_data_8bit(0x08);
    lcd_send_data_8bit(0x08);
    lcd_send_data_8bit(0x26);
    lcd_send_data_8bit(0x2A);

    lcd_send_command(0xF1);    
    lcd_send_data_8bit(0x43);
    lcd_send_data_8bit(0x70);
    lcd_send_data_8bit(0x72);
    lcd_send_data_8bit(0x36);
    lcd_send_data_8bit(0x37);  
    lcd_send_data_8bit(0x6F);


    lcd_send_command(0xF2);   
    lcd_send_data_8bit(0x45);
    lcd_send_data_8bit(0x09);
    lcd_send_data_8bit(0x08);
    lcd_send_data_8bit(0x08);
    lcd_send_data_8bit(0x26);
    lcd_send_data_8bit(0x2A);

    lcd_send_command(0xF3);   
    lcd_send_data_8bit(0x43);
    lcd_send_data_8bit(0x70);
    lcd_send_data_8bit(0x72);
    lcd_send_data_8bit(0x36);
    lcd_send_data_8bit(0x37); 
    lcd_send_data_8bit(0x6F);

    lcd_send_command(0xED);	
    lcd_send_data_8bit(0x1B); 
    lcd_send_data_8bit(0x0B); 

    lcd_send_command(0xAE);			
    lcd_send_data_8bit(0x77);
    
    lcd_send_command(0xCD);			
    lcd_send_data_8bit(0x63);		


    lcd_send_command(0x70);			
    lcd_send_data_8bit(0x07);
    lcd_send_data_8bit(0x07);
    lcd_send_data_8bit(0x04);
    lcd_send_data_8bit(0x0E); 
    lcd_send_data_8bit(0x0F); 
    lcd_send_data_8bit(0x09);
    lcd_send_data_8bit(0x07);
    lcd_send_data_8bit(0x08);
    lcd_send_data_8bit(0x03);

    lcd_send_command(0xE8);			
    lcd_send_data_8bit(0x34);

    lcd_send_command(0x62);			
    lcd_send_data_8bit(0x18);
    lcd_send_data_8bit(0x0D);
    lcd_send_data_8bit(0x71);
    lcd_send_data_8bit(0xED);
    lcd_send_data_8bit(0x70); 
    lcd_send_data_8bit(0x70);
    lcd_send_data_8bit(0x18);
    lcd_send_data_8bit(0x0F);
    lcd_send_data_8bit(0x71);
    lcd_send_data_8bit(INTER_REG_ENABLE2);
    lcd_send_data_8bit(0x70); 
    lcd_send_data_8bit(0x70);

    lcd_send_command(0x63);			
    lcd_send_data_8bit(0x18);
    lcd_send_data_8bit(0x11);
    lcd_send_data_8bit(0x71);
    lcd_send_data_8bit(0xF1);
    lcd_send_data_8bit(0x70); 
    lcd_send_data_8bit(0x70);
    lcd_send_data_8bit(0x18);
    lcd_send_data_8bit(0x13);
    lcd_send_data_8bit(0x71);
    lcd_send_data_8bit(0xF3);
    lcd_send_data_8bit(0x70); 
    lcd_send_data_8bit(0x70);

    lcd_send_command(0x64);			
    lcd_send_data_8bit(0x28);
    lcd_send_data_8bit(0x29);
    lcd_send_data_8bit(0xF1);
    lcd_send_data_8bit(0x01);
    lcd_send_data_8bit(0xF1);
    lcd_send_data_8bit(0x00);
    lcd_send_data_8bit(0x07);

    lcd_send_command(0x66);			
    lcd_send_data_8bit(0x3C);
    lcd_send_data_8bit(0x00);
    lcd_send_data_8bit(0xCD);
    lcd_send_data_8bit(0x67);
    lcd_send_data_8bit(0x45);
    lcd_send_data_8bit(0x45);
    lcd_send_data_8bit(0x10);
    lcd_send_data_8bit(0x00);
    lcd_send_data_8bit(0x00);
    lcd_send_data_8bit(0x00);

    lcd_send_command(0x67);			
    lcd_send_data_8bit(0x00);
    lcd_send_data_8bit(0x3C);
    lcd_send_data_8bit(0x00);
    lcd_send_data_8bit(0x00);
    lcd_send_data_8bit(0x00);
    lcd_send_data_8bit(0x01);
    lcd_send_data_8bit(0x54);
    lcd_send_data_8bit(0x10);
    lcd_send_data_8bit(0x32);
    lcd_send_data_8bit(0x98);

    lcd_send_command(0x74);			
    lcd_send_data_8bit(0x10);	
    lcd_send_data_8bit(0x85);	
    lcd_send_data_8bit(0x80);
    lcd_send_data_8bit(0x00); 
    lcd_send_data_8bit(0x00); 
    lcd_send_data_8bit(0x4E);
    lcd_send_data_8bit(0x00);					
    
    lcd_send_command(0x98);			
    lcd_send_data_8bit(0x3e);
    lcd_send_data_8bit(0x07);

    lcd_send_command(0x35);	
    lcd_send_command(0x21);

    lcd_send_command(0x11);
    Delay_ms(120);
    lcd_send_command(0x29);
    Delay_ms(20);
}

/********************************************************************************
function:	Set the resolution and scanning method of the screen
parameter:
		Scan_dir:   Scan direction
********************************************************************************/
static void lcd_set_attributes(uint8_t Scan_dir)
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
    lcd_send_command(0x36); //MX, MY, RGB mode
    //LCD_1IN28_SendData_8Bit(MemoryAccessReg);	//0x08 set RGB
    lcd_send_data_8bit(MemoryAccessReg);	//0x08 set RGB
}


/********************************************************************************
function:	Sets the start position and size of the display area
parameter:
		Xstart 	:   X direction Start coordinates
		Ystart  :   Y direction Start coordinates
		Xend    :   X direction end coordinates
		Yend    :   Y direction end coordinates
********************************************************************************/
void lcd_set_windows(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend)
{
    //set the X coordinates
    lcd_send_command(0x2A);
    lcd_send_data_8bit(0x00);
    lcd_send_data_8bit(Xstart);
    lcd_send_data_8bit((Xend-1)>>8);
    lcd_send_data_8bit(Xend-1);

    //set the Y coordinates
    lcd_send_command(0x2B);
    lcd_send_data_8bit(0x00);
    lcd_send_data_8bit(Ystart);
    lcd_send_data_8bit((Xend-1)>>8);
    lcd_send_data_8bit(Yend-1);

    lcd_send_command(0X2C);
}

/**
 * @brief Initialise the LCD
 * @param scan_dir - scan direction, HORIZONTAL is standard
 * @param brightness - Screen brightness - a value between 0-100
 */
void lcd_init(uint8_t scan_dir, uint8_t brightness)
{

    // STDIO_INIT_ALL();

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
    PWM_Set_Clkdiv_Int(slice_num, 50);
    PWM_Set_Enabled(slice_num, true);
    
    /* SPI Initialisation */
    SPI_Init(LCD_SPI_PORT, 40000 * 1000);
    GPIO_Set_Function(LCD_CLK_PIN, GPIO_FUNCTION_SPI);
    GPIO_Set_Function(LCD_MOSI_PIN, GPIO_FUNCTION_SPI);

    /* Reset and configure registers */
    //Hardware reset
    lcd_reset();

    //Set the resolution and scanning method of the screen
    lcd_set_attributes(scan_dir);
    
    // Initialises register values
    lcd_init_regs();

    /* Turn on the backlight at 50% brightness */
    PWM_Set_Chan_Level(slice_num, PWM_CHANNEL_B, brightness);

    /* Set the window size to the whole screen */
    lcd_set_windows(0, 0, LCD_1IN28_WIDTH, LCD_1IN28_HEIGHT);
}


/******************************************************************************
function :	Clear screen
parameter:
******************************************************************************/
void lcd_clear(uint16_t Color)
{
    uint16_t j;
    uint16_t row[LCD_1IN28_WIDTH];

    // Fix endianness
    Color = ((Color<<7)&0xff00)|(Color>>8);

    for (j = 0; j < LCD_1IN28_WIDTH; j++) {
        row[j] = Color;
        // row[j] = 0xffff;
    }

    // WARNING: This function still uses 16 bit colour, and sends
    // framebuffers via CPU controlled SPI

    GPIO_Write(LCD_DC_PIN, 1);
    for(int j = 0; j < LCD_1IN28_HEIGHT; j++) {
        // for(int i = 0; i < LCD_1IN28_WIDTH; i++) {
        SPI_Write_n_Bytes(LCD_SPI_PORT, (uint8_t *)row, LCD_1IN28_WIDTH*2);
        //     SPI_Write_Byte(LCD_SPI_PORT, 0xf8);
        //     SPI_Write_Byte(LCD_SPI_PORT, 0x00);
        // }
    }
}

/******************************************************************************
function :	Sends the image buffer in RAM to display
parameter:
******************************************************************************/
void lcd_display(uint8_t *Image)
{

    // GPIO_Write(LCD_DC_PIN, 1);
    //
    // // DMA Config 
    // // By default, the read address increments after each transfer
    // // Our transfer size is 16 bits per transfer, so that makes 240*240*3/2 transfers
    //
    // const uint32_t transfer_count = 57600;
    // const uint32_t dma_chan = dma_claim_unused_channel(true);
    // dma_channel_config c = dma_channel_get_default_config(dma_chan);
    // channel_config_set_transfer_data_size(&c, DMA_SIZE_8); // The SPI registers are 16 bits on the RP2040
    // channel_config_set_dreq(&c, spi_get_dreq(spi1, true));
    // dma_channel_configure(
    //     dma_chan,
    //     &c,
    //     &spi_get_hw(spi1)->dr, // write address - not certain of what spi_get_hw does - it seems to simply return a pointer to the passed SPI instance if it's hardware spi, and do nothing if not
    //     Image, // read address
    //     dma_encode_transfer_count(transfer_count), // element count
    //     true  //  start transfer immediately
    // );
    //
    // // Wait for it to finish
    // dma_channel_wait_for_finish_blocking(dma_chan);
    // while (spi_is_busy(spi1)) {
    //     tight_loop_contents();
    // }

}
