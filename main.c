#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "lcd.h"
#include "rasteriser.h"
#include "settings.h"
#include "types/fixed-point.h"
#include "types/matrix.h"
#include "types/misc.h"
#include "types/vector.h"
#include "cube.h"

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

void simple_square(uint16_t *FBuffer)
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

void triangle_board(uint16_t *FBuffer)
{

    vertex vertices[3] = {
        (vertex) {(vec3q16) {FLOAT_TO_Q16(-0.7), FLOAT_TO_Q16(-0.7)}, (col3ub) {217, 63, 36}},
        (vertex) {(vec3q16) {FLOAT_TO_Q16(-0.7), FLOAT_TO_Q16(-0.35)}, (col3ub) {105, 47, 35}},
        (vertex) {(vec3q16) {FLOAT_TO_Q16(-0.35), FLOAT_TO_Q16(-0.7)}, (col3ub) {52, 35, 49}},
    };

    /* Rasterise the triangles */
    for (uint8_t i = 0; i < 16; i++) {
        vec3q16 translation = {FLOAT_TO_Q16(0.35)*(i%4), FLOAT_TO_Q16(0.35)*(i/4)};
        draw(&(draw_command) {
                .mesh = {
                    .vertices = vertices,
                    .count = 3,
                },
                .cull_mode = NO_CULL,
                .transform = translate(&translation)
             }
        );
    }
    // Push the framebuffer to the display
    LCD_1IN28_Display(FBuffer);
    DEV_Delay_ms(1000000);
}


void spin_rectangle(uint16_t *FBuffer)
{
    vertex vertices[] = {
        // (vertex) {(vec3q16) {FLOAT_TO_Q16(-0.5), FLOAT_TO_Q16(-0.5)}, (col3ub) {230, 39, 120}},
        // (vertex) {(vec3q16) {FLOAT_TO_Q16(-0.5), FLOAT_TO_Q16(0.5)}, (col3ub) {214, 25, 146}},
        // (vertex) {(vec3q16) {FLOAT_TO_Q16(0.5), FLOAT_TO_Q16(-0.5)}, (col3ub) {223, 209, 208}},
        // (vertex) {(vec3q16) {FLOAT_TO_Q16(0.5), FLOAT_TO_Q16(0.5)}, (col3ub) {244, 236, 230}},
        (vertex) {(vec3q16) {FLOAT_TO_Q16(-0.5), FLOAT_TO_Q16(-0.5)}, (col3ub) {255, 0, 0}},
        (vertex) {(vec3q16) {FLOAT_TO_Q16(-0.5), FLOAT_TO_Q16(0.5)}, (col3ub) {0, 255, 0}},
        (vertex) {(vec3q16) {FLOAT_TO_Q16(0.5), FLOAT_TO_Q16(-0.5)}, (col3ub) {0, 0, 255}},
        (vertex) {(vec3q16) {FLOAT_TO_Q16(0.5), FLOAT_TO_Q16(0.5)}, (col3ub) {255, 255, 255}},
    };

    uint32_t indices[] = {
        0, 1, 2,
        3, 2, 1
    };

    int time = 0;

    while (1) {

        matrix4q16 xz_rot = rotateXZ(time);
        matrix4q16 xy_rot = rotateXY(90);
        matrix4q16 transform = mat_mat_multq16(&xz_rot, &xy_rot);

        /* Clear the screen */
        Paint_Clear(WHITE);

        /* Rasterise */
        draw(&(draw_command) {
                .mesh = {
                    .vertices = vertices,
                    .indices = indices,
                    .count = 6,
                },
                .cull_mode = NO_CULL,
                .transform = transform
             }
        );

        /* Push the framebuffer to the display */
        LCD_1IN28_Display(FBuffer);

        if (time == 720) {
            time = 1;
        }

        time += 2;
    }
}


void spin_cube(uint16_t *FBuffer)
{

    int time = 0;

    while (1) {

        matrix4q16 xz_rot = rotateXZ(time);
        matrix4q16 xy_rot = rotateXY(time * 2);
        matrix4q16 scale = scale_by_scalar(Q16_HALF);

        matrix4q16 intermediate = mat_mat_multq16(&xz_rot, &xy_rot);
        matrix4q16 transform = mat_mat_multq16(&scale, &intermediate);

        /* Clear the screen */
        Paint_Clear(WHITE);

        /* Rasterise */
        draw(&(draw_command) {
                .mesh = cube,
                .cull_mode = CW,
                .transform = transform
             }
        );

        /* Push the framebuffer to the display */
        LCD_1IN28_Display(FBuffer);

        if (time == 720) {
            time = 2;
        }

        time += 2;
    }
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
    // triangle_board(fb);
    // simple_triangle(fb);
    spin_cube(fb);
    // spin_rectangle(fb);
    
    
    /* Module Exit */
    free(fb);
    fb = NULL;
    DEV_Module_Exit();
    return 0;
}
