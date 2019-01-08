/*! 
* @file mcp300x.c
*
* @brief Simple driver for the Microchip MCP3004/8 ADC.
*
* @author Xavier Garcia Herrera.
*
* @par
* Xavier Garcia Herrera
* Version 1.0 2016
*/
#include "mcp300x.h"

void mcp300x_spi_init(void)
{

  /*!
  SPI clock out data on the falling edge and latch data on the rising edge
  SPI mode 0
  Max Clk 3.4MHz@5V
  Max Clk 1MHz@3V
  */
  
  setup_spi2(SPI_MASTER | SPI_SCK_IDLE_LOW | SPI_XMIT_L_TO_H | SPI_CLK_DIV_16);
  // setup_spi2(SPI_MASTER | SPI_SCK_IDLE_LOW | SPI_XMIT_L_TO_H | SPI_CLK_DIV_64);
}

uint16_t mcp300x_read_single(mcp300x_channel_t channel)
{
  /*!
  An ADC conversion is made of sending 2 bytes
  The first byte is the sequence:
  0 0 0 0 0 0 0 1
  The second byte is the sequence:
  S/D D2 D1 D0 X X X X
  Where S/D selects between differential(0) and single(1) ended operation.
  D2, D1 and D0 selects the input channel.

  For MCP3004:
             D2  D1  D0
  Channel 0   0   0   0
  Channel 1   0   0   1
  Channel 2   0   1   0
  Channel 3   0   1   1

  For MCP3008

  Channel 4   1   0   0
  Channel 5   1   0   1
  Channel 6   1   1   0
  Channel 7   1   1   1

  After the second byte, the slave returns the sequence:
  ? ? ? ? ? N B9 B8
  Where ? can be any value, N is a null bit, always 0.
  Then read the next byte, writing anything to the slave.
  The slave should return:
  B7 B6 B5 B4 B3 B2 B1 B0

  B9 to B0 is a 10 bit result of the ADC conversion
  */
  
  uint8_t channel_byte, data_msb, data_lsb;

  channel_byte = (MCP300X_SINGLE_MASK|(channel << 4));

  output_low(MCP300X_CS);
  delay_us(10);
  spi_write2(MCP300X_CONTROL);

  data_msb = spi_read2(channel_byte); //write the last byte and read the first byte with B9 - B8
  data_lsb = spi_read2(0); //read B7-B8 by writing any value
  data_msb &= MCP300X_READ_MASK; //only the first two bits B9 - B8

  output_high(MCP300X_CS);
  
  return make16(data_msb,data_lsb);
}