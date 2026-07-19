#include <stdint.h>


#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "LCD_1in28.h"
#include "rasteriser.h"
#include "settings.h"
#include "types/fixed-point.h"
#include "types/matrix.h"
#include "types/misc.h"
#include "types/vector.h"


// uint32_t Imagesize = LCD_1IN28_HEIGHT * LCD_1IN28_WIDTH * 2;
// uint16_t *FBuffer;
// if ((FBuffer = (uint16_t *)malloc(Imagesize)) == NULL)
// {
//     printf("Framebuffer malloc failed! Not enough memory.");
//     exit(0);
// }

#define LCD_SCREEN_SIZE 240*240

static uint16_t FBuffer[LCD_SCREEN_SIZE] = {0};


void simple_square()
{
    vertex vertices[] = {
        (vertex) {(vec3q16) {FLOAT_TO_Q16(-0.7), FLOAT_TO_Q16(-0.7)}, (col3ub) {255, 0, 0}},
        (vertex) {(vec3q16) {FLOAT_TO_Q16(-0.7), FLOAT_TO_Q16(-0.35)}, (col3ub) {0, 255, 0}},
        (vertex) {(vec3q16) {FLOAT_TO_Q16(-0.35), FLOAT_TO_Q16(-0.7)}, (col3ub) {0, 0, 255}},
        (vertex) {(vec3q16) {FLOAT_TO_Q16(-0.35), FLOAT_TO_Q16(-0.35)}, (col3ub) {255, 255, 255}},
    };

    uint32_t indices[] = {
        0, 1, 2,
        3, 2, 1
    };

    /* Rasterise the triangle */
    draw(&(draw_command) {
            .mesh = {
                .vertices = vertices,
                .indices = indices,
                .count = 6,
            },
            .cull_mode = NO_CULL,
            .transform = mat4_id()
         }
    );
    // Push the framebuffer to the display
    LCD_1IN28_Display(FBuffer);
    DEV_Delay_ms(1000000);
}



int main(void)
{
    // Initialises GPIOs, SPI, I2C, ADC, PWM, etc.
    if (DEV_Module_Init() != 0)
    {
        return -1;
    }

    LCD_1IN28_Init(HORIZONTAL);
    LCD_1IN28_Clear(WHITE);

    DEV_SET_PWM(100);

    /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
    Paint_NewImage((uint8_t *)FBuffer, LCD_1IN28.WIDTH, LCD_1IN28.HEIGHT, WHITE);
    // Set background to white
    Paint_Clear(WHITE);

    // Wait, so we can reflash in case of errors
    DEV_Delay_ms(1000);

    // Push the framebuffer to the display
    LCD_1IN28_Display(FBuffer);
    DEV_Delay_ms(1000);

    /* Draw function */

    // Paint_SetPixel(0, 120, RED);
    // Paint_SetPixel(0, 125, BLUE);
    // Paint_SetPixel(0, 20, BLACK);
    // Paint_SetPixel(0, 220, BLACK);
    // Paint_SetPixel(50, 120, RED);
    // Paint_SetPixel(50, 125, BLUE);
    // Paint_SetPixel(50, 20, BLACK);
    // Paint_SetPixel(50, 220, BLACK);
    // Paint_SetPixel(100, 120, RED);
    // Paint_SetPixel(100, 125, BLUE);
    // Paint_SetPixel(100, 20, BLACK);
    // Paint_SetPixel(100, 220, BLACK);
    // LCD_1IN28_Display(FBuffer);
    // DEV_Delay_ms(100000000);


    // triangle_board(FBuffer);
    simple_square();
    // spin_rectangle(FBuffer);
    
    
    /* Module Exit */
    // free(FBuffer);
    // FBuffer = NULL;
    DEV_Module_Exit();
    return 0;
}
