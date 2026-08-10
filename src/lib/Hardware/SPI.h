#ifndef _SPI_H_
#define _SPI_H_

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    SPI_PORT_0 = 0,
    SPI_PORT_1
} SPI_Port;

void SPI_Init(SPI_Port port, uint32_t baud);
void SPI_Write_Byte(SPI_Port port, uint8_t value);
void SPI_Write_n_Bytes(SPI_Port port, uint8_t pdata[], uint32_t len);
int SPI_Get_Dreq(SPI_Port port, bool is_tx);
volatile uint32_t *SPI_Data_Reg_Addr(SPI_Port port);

#endif // _SPI_H_
