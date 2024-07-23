#ifndef BSP_IIC_H_
#define BSP_IIC_H_
#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>

void bsp_iic_init (uint8_t SlaveAddr);
void iic_write(uint8_t address,uint8_t data);
uint8_t iic_read(uint8_t address);
int iic_write_len(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);
int iic_read_len(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf);
extern void IIC_TX_ISR(void);





#endif /* SRC_BSP_IIC_H_ */
