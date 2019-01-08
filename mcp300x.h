/*! 
* @file mcp300x.h
*
* @brief Simple driver for the Microchip MCP3004/8 ADC.
*
* @author Xavier Garcia Herrera.
*
* @par
* Xavier Garcia Herrera
* Version 1.0 2016
*/

#ifndef _MCP300X_H
#define _MCP300X_H

#include <stdint.h> //generic typedefs
#include <stdbool.h> //bool typedef

/*!
  MCP73004/8 Channel Select
*/
typedef enum
{
  MCP300X_CHANNEL_0 = 0,   /*!< MCP3004/8 ADC Channel 0 */
  MCP300X_CHANNEL_1,       /*!< MCP3004/8 ADC Channel 1 */
  MCP300X_CHANNEL_2,       /*!< MCP3004/8 ADC Channel 2 */
  MCP300X_CHANNEL_3,       /*!< MCP3004/8 ADC Channel 3 */
  MCP300X_CHANNEL_4,       /*!< MCP3004/8 ADC Channel 4 */
  MCP300X_CHANNEL_5,       /*!< MCP3004/8 ADC Channel 5 */
  MCP300X_CHANNEL_6,       /*!< MCP3004/8 ADC Channel 6 */
  MCP300X_CHANNEL_7,       /*!< MCP3004/8 ADC Channel 7 */
} mcp300x_channel_t;

/*! @name MCP73004/8 Definitions
** @{
*/
/*!
  Commands
*/
#define MCP300X_CONTROL       0x01        /*!< MCP3004/8 Control byte */
#define MCP300X_SINGLE_MASK   0x80       /*!< MCP3004/8 Single ended operation mask */
#define MCP300X_READ_MASK     0x03       /*!< MCP3004/8 Single ended msb byte mask */
/*!
  Pin definitions
*/
#ifndef MCP300X_CS
#define MCP300X_CS PIN_C0
#endif
/** @} */

/* Function prototypes*/
void 
mcp300x_spi_init(void);

uint16_t 
mcp300x_read_single(mcp300x_channel_t channel);

#endif /* _MCP300X_H */
