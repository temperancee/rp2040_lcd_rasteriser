#ifndef _SPI_H_
#define _SPI_H_

#include <stdint.h>

typedef enum {
    SPI_PORT_0 = 0,
    SPI_PORT_1
} SPI_Port;

void SPI_Init(SPI_Port port, uint32_t baud);
void SPI_Write_Byte(SPI_Port port, uint8_t value);
void SPI_Write_n_Bytes(SPI_Port port, uint8_t pdata[], uint32_t len);

#endif // _SPI_H_
