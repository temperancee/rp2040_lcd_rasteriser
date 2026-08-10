#include "SPI.h"

#include <stdint.h>

#include "hardware/spi.h"

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

/**
 * @brief Used for DMA. Gets the DREQ for the passed SPI instance
 * @param port - the SPI port to use
 * @param is_tx - true for sending, false for receiving
 * @return The DREQ for this SPI instance
 */
int SPI_Get_Dreq(SPI_Port port, bool is_tx)
{
    return spi_get_dreq(SPI_Instances[port], is_tx);
}

/**
 * @brief Used for DMA. Gets the data register of the passed SPI instance
 * @param port - the SPI port to use
 * @return Address of the data register for this port
 */
volatile uint32_t *SPI_Data_Reg_Addr(SPI_Port port)
{
    return &spi_get_hw(SPI_Instances[port])->dr;
}
