
#include "DMA.h"

#include <stdbool.h>
#include <stdint.h>

#include "hardware/dma.h"

uint32_t DMA_Claim_Unused_Channel(void)
{
    return dma_claim_unused_channel(true);   
}

void DMA_Configure_Channel(uint32_t channel, volatile void *write_addr, volatile void const *read_addr, DMA_Transfer_Size transfer_size, uint32_t transfer_count, uint32_t dreq, bool start_immediately)
{
    dma_channel_config c = dma_channel_get_default_config(channel);
    channel_config_set_transfer_data_size(&c, (dma_channel_transfer_size_t) transfer_size); // The SPI registers are 16 bits on the RP2040
    channel_config_set_dreq(&c, dreq);
    dma_channel_configure(
        channel,
        &c,
        write_addr,
        read_addr,
        dma_encode_transfer_count(transfer_count),
        start_immediately
    );
}

void DMA_Wait_For_Finish_Blocking(uint32_t channel)
{
    dma_channel_wait_for_finish_blocking(channel);
}
