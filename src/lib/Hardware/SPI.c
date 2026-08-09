#include "SPI.h"
#include <hardware/spi.h>

// Allows files to import SPI.h without knowing about spi0 and spi1,
// instead, they use SPI_PORT_0/1 as defined in the header, which are
// used to index this array
static spi_inst_t* const SPI_Instances[2] = { spi0, spi1 };

void SPI_Init(SPI_Port port, uint32_t baud)
{
    spi_init(SPI_Instances[port], baud);
}

void SPI_Write_Byte(SPI_Port port, uint8_t value)
{
    spi_write_blocking(SPI_Instances[port], &value, 1);
}

void SPI_Write_n_Bytes(SPI_Port port, uint8_t pdata[], uint32_t len)
{
    spi_write_blocking(SPI_Instances[port], pdata, len);
}
