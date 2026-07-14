#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "LCD_1in28.h"
#include "images.h"
#include <stdint.h>
#include "rasteriser.h"
#include "types/fixed-point.h"
#include "types/matrix.h"
#include "types/misc.h"
#include "types/vector.h"

uint16_t *init(void)
{
    LCD_1IN28_Init(HORIZONTAL);
    LCD_1IN28_Clear(WHITE);

    DEV_SET_PWM(100);
    // This is a 16bit colour depth LCD, so 2 bytes per pixel
    uint32_t Imagesize = LCD_1IN28_HEIGHT * LCD_1IN28_WIDTH * 2;
    // uint32_t Imagesize = (LCD_1IN28_HEIGHT * LCD_1IN28_WIDTH) >> 8;
    // This is our framebuffer
    uint16_t *FBuffer;
    if ((FBuffer = (uint16_t *)malloc(Imagesize)) == NULL)
    {
        printf("Framebuffer malloc failed! Not enough memory.");
        exit(0);
    }
    /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
    Paint_NewImage((uint8_t *)FBuffer, LCD_1IN28.WIDTH, LCD_1IN28.HEIGHT, ROTATE_0, WHITE);
    // Use 65k colour
    Paint_SetScale(65);
    // Set background to white
    Paint_Clear(WHITE);
    // Push the framebuffer to the display
    LCD_1IN28_Display(FBuffer);
    DEV_Delay_ms(1000);
    return FBuffer;
}

void draw_pippa(uint16_t *FBuffer)
{
    Paint_DrawPoint(50, 41, BLACK, DOT_PIXEL_1X1, DOT_FILL_RIGHTUP); // 240 240
    Paint_DrawPoint(50, 46, BLACK, DOT_PIXEL_2X2, DOT_FILL_RIGHTUP);
    Paint_DrawPoint(50, 51, BLACK, DOT_PIXEL_3X3, DOT_FILL_RIGHTUP);
    Paint_DrawPoint(50, 56, BLACK, DOT_PIXEL_4X4, DOT_FILL_RIGHTUP);
    Paint_DrawPoint(50, 61, BLACK, DOT_PIXEL_5X5, DOT_FILL_RIGHTUP);

    Paint_DrawLine(60, 40, 90, 70, MAGENTA, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
    Paint_DrawLine(60, 70, 90, 40, MAGENTA, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

    Paint_DrawRectangle(60, 40, 90, 70, RED, DOT_PIXEL_2X2, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(100, 40, 130, 70, BLUE, DOT_PIXEL_2X2, DRAW_FILL_FULL);

    Paint_DrawLine(135, 55, 165, 55, CYAN, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(150, 40, 150, 70, CYAN, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);

    Paint_DrawCircle(150, 55, 15, GREEN, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(185, 55, 15, GREEN, DOT_PIXEL_1X1, DRAW_FILL_FULL);

    Paint_DrawNum(50, 80, 9.87654321, &Font20, 3, WHITE, BLACK);
    Paint_DrawString_EN(50, 161, "I be movin' chicken nugget", &Font16, RED, WHITE);
    LCD_1IN28_Display(FBuffer);
    DEV_Delay_ms(5000);

    /* Draw Pippa */
    // This command draws the image to the framebuffer
    Paint_DrawImage(pippa_square, 0, 0, PIPPA_SQUARE_WIDTH, PIPPA_SQUARE_HEIGHT);
    Paint_DrawString_EN(50, 161, "I love you <3", &Font16, RED, WHITE);
    // This prints the framebuffer to the LCD
    LCD_1IN28_Display(FBuffer);
    DEV_Delay_ms(1000);

    /* Add butterfly */
    Paint_DrawImage(butterfly, 4, 70, BUTTERFLY_WIDTH, BUTTERFLY_HEIGHT);
    LCD_1IN28_Display(FBuffer);
    DEV_Delay_ms(1000);

}

void swagaholic(uint16_t *FBuffer)
{
    // DRAW
    while (true) {
        Paint_DrawImage(skeleton, 0, 0, SKELETON_WIDTH, SKELETON_HEIGHT);
        LCD_1IN28_Display(FBuffer);
        DEV_Delay_ms(1000);
        Paint_DrawString_EN(88, 20, "SWAG", &Font24, RED, BLACK);
        LCD_1IN28_Display(FBuffer);
        DEV_Delay_ms(1000);
        Paint_DrawString_EN(75, 175, "AHOLIC", &Font24, RED, BLACK);
        LCD_1IN28_Display(FBuffer);
        DEV_Delay_ms(1000);
    }
}

void simple_triangle(uint16_t *FBuffer)
{
    // {217, 63, 36}
    // {105, 47, 35}
    // {52, 35, 49}

    vertex vertices[3] = {
        // (vertex) {(vec3q16) {0, Q16_HALF}, (col3ub) {255, 0, 0}},
        // (vertex) {(vec3q16) {-Q16_HALF, -Q16_HALF}, (col3ub) {0, 255, 0}},
        // (vertex) {(vec3q16) {Q16_HALF, -Q16_HALF}, (col3ub) {0, 0, 255}},
        // (vertex) {(vec3q16) {0, Q16_ONE}, (col3ub) {255, 0, 0}},
        // (vertex) {(vec3q16) {-Q16_ONE, -Q16_ONE}, (col3ub) {255, 0, 0}},
        // (vertex) {(vec3q16) {Q16_ONE, -Q16_ONE}, (col3ub) {0, 255, 0}},
        (vertex) {(vec3q16) {FLOAT_TO_Q16(-0.7), FLOAT_TO_Q16(-0.7)}, (col3ub) {217, 63, 36}},
        (vertex) {(vec3q16) {FLOAT_TO_Q16(-0.7), FLOAT_TO_Q16(-0.35)}, (col3ub) {105, 47, 35}},
        (vertex) {(vec3q16) {FLOAT_TO_Q16(-0.35), FLOAT_TO_Q16(-0.7)}, (col3ub) {52, 35, 49}},
    };

    /* Rasterise the triangle */
    draw(&(draw_command) {
            .mesh = {
                .vertices = vertices,
                .vertex_count = 3,
            },
            .cull_mode = NO_CULL,
            .transform = mat4_id()
         }
    );
    // Push the framebuffer to the display
    LCD_1IN28_Display(FBuffer);
    DEV_Delay_ms(1000000);
}

void triangle_board(uint16_t *FBuffer)
{
    // vec3f vertices[9] = {
    //     (vec3f) {40, 189},
    //     (vec3f) {120, 189},
    //     (vec3f) {80, 120},
    //     (vec3f) {200, 189},
    //     (vec3f) {120, 189},
    //     (vec3f) {160, 120},
    //     (vec3f) {80, 120},
    //     (vec3f) {120, 51},
    //     (vec3f) {160, 120},
    // };

    vertex vertices[3] = {
        (vertex) {(vec3q16) {FLOAT_TO_Q16(-0.7), FLOAT_TO_Q16(-0.7)}, (col3ub) {217, 63, 36}},
        (vertex) {(vec3q16) {FLOAT_TO_Q16(-0.7), FLOAT_TO_Q16(-0.35)}, (col3ub) {105, 47, 35}},
        (vertex) {(vec3q16) {FLOAT_TO_Q16(-0.35), FLOAT_TO_Q16(-0.7)}, (col3ub) {52, 35, 49}},
    };

    /* Rasterise the triangles */
    for (uint8_t i = 0; i < 16; i++)
        draw(&(draw_command) {
                .mesh = {
                    .vertices = vertices,
                    .vertex_count = 3,
                },
                .cull_mode = NO_CULL,
                .transform = homog_id_xy(FLOAT_TO_Q16(0.35)*(i%4), FLOAT_TO_Q16(0.35)*(i/4))
                // .transform = homog_id_xy(0, 0)
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

    // Initialise scene 
    uint16_t *fb = init();

    // Draw function
    triangle_board(fb);
    // simple_triangle(fb);
    
    
    /* Module Exit */
    free(fb);
    fb = NULL;
    DEV_Module_Exit();
    return 0;
}
