/**
 * \file
 *
 * \brief SPI basic driver.
 *
 (c) 2020 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms,you may use this software and
    any derivatives exclusively with Microchip products.It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

/**
 * \defgroup doc_driver_spi_init SPI Init
 * \ingroup doc_driver_spi
 *
 * \section doc_driver_spi_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */
#include <spi.h>

/**
 * \brief Initialize spi interface
 * \return Initialization status
 */
int8_t SPI_0_init()
{

	SPI0.CTRLA = 0 << SPI_CLK2X_bp     /* Enable Double Speed: disabled */
	             | 0 << SPI_DORD_bp    /* Data Order Setting: disabled */
	             | 1 << SPI_ENABLE_bp  /* Enable Module: enabled */
	             | 1 << SPI_MASTER_bp  /* SPI module in master mode */
	             | SPI_PRESC_DIV16_gc; /* System Clock / 16 */

	SPI0.CTRLB = 0 << SPI_BUFEN_bp   /* Buffer Mode Enable: disabled */
	             | 0 << SPI_BUFWR_bp /* Buffer Write Mode: disabled */
	             | SPI_MODE_0_gc     /* SPI Mode 0 */
	             | 1 << SPI_SSD_bp;  /* Slave Select Disable: enabled */

	// SPI0.INTCTRL = 0 << SPI_DREIE_bp /* Data Register Empty Interrupt Enable: disabled */
	//		 | 0 << SPI_IE_bp /* Interrupt Enable: disabled */
	//		 | 0 << SPI_RXCIE_bp /* Receive Complete Interrupt Enable: disabled */
	//		 | 0 << SPI_SSIE_bp /* Slave Select Trigger Interrupt Enable: disabled */
	//		 | 0 << SPI_TXCIE_bp; /* Transfer Complete Interrupt Enable: disabled */

	return 0;
}
