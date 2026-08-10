#ifndef _DMA_H_
#define _DMA_H_

#include <stdbool.h>
#include <stdint.h>


typedef enum {
    DMA_8_BITS, DMA_16_BITS, DMA_32_BITS 
} DMA_Transfer_Size;

uint32_t DMA_Claim_Unused_Channel(void);
void DMA_Configure_Channel(uint32_t channel, volatile void *write_addr, volatile void const *read_addr, DMA_Transfer_Size transfer_size,  uint32_t transfer_count, uint32_t dreq, bool start_immediately);
void DMA_Wait_For_Finish_Blocking(uint32_t channel);

#endif // _DMA_H_
