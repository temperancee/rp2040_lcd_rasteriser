#ifndef _SPI_H_
#define _SPI_H_

#include <stdint.h>
#include <hardware/spi.h>

// This enum and array provide the modules which include this
// file to pass a port, without having to expose the hardware/spi.h
// file to the modules directly, allowing for this module to be mocked

typedef enum {
    SPI_PORT_0 = 0,
    SPI_PORT_1
} SPI_Port;

static spi_inst_t* const SPI_Instances[2] = { spi0, spi1 };


static inline void SPI_Init(SPI_Port port, uint32_t baud)
{
    spi_init(SPI_Instances[port], baud);
}

static inline void SPI_Write_Byte(SPI_Port port, uint8_t value)
{
    spi_write_blocking(SPI_Instances[port], &value, 1);
}

static inline void SPI_Write_n_Bytes(SPI_Port port, uint8_t pdata[], uint32_t len)
{
    spi_write_blocking(SPI_Instances[port], pdata, len);
}

#endif // _SPI_H_
