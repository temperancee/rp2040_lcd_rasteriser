
#include <stdint.h>
#include <stddef.h>

#include "types/colour.h"

typedef struct {
    col3ub * pixels;
    uint8_t width;
    uint8_t height;
} image_view;

static inline void initialise_image_view(image_view *iv)
{
    iv->pixels = NULL;
    // width and heigh initialised to 0 by default
}
