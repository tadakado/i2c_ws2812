/**
 * \file
 *
 * \brief CCL related functionality implementation.
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
 * \addtogroup doc_driver_ccl
 *
 * \section doc_driver_ccl_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */
#include <ccl.h>

/**
 * \brief Initialize CCL peripheral
 * \return Return value 0 if success
 */
int8_t DIGITAL_GLUE_LOGIC_0_init()
{

	// Enable Protected register, peripheral must be disabled (ENABLE=0, in TCD.LUT0CTRLA).

	// CCL.SEQCTRL0 = CCL_SEQSEL_DISABLE_gc; /* Sequential logic disabled */

	// CCL.TRUTH0 = 0; /* Truth 0: 0 */

	// CCL.LUT0CTRLC = CCL_INSEL2_MASK_gc /* Masked input */;

	// CCL.LUT0CTRLB = CCL_INSEL0_MASK_gc /* Masked input */
	//		 | CCL_INSEL1_MASK_gc /* Masked input */;

	// CCL.LUT0CTRLA = 0 << CCL_CLKSRC_bp /* Clock Source Selection: disabled */
	//		 | CCL_EDGEDET_DIS_gc /* Edge detector is disabled */
	//		 | CCL_FILTSEL_DISABLE_gc /* Filter disabled */
	//		 | 0 << CCL_ENABLE_bp /* LUT Enable: disabled */
	//		 | 0 << CCL_OUTEN_bp; /* Output Enable: disabled */

	CCL.TRUTH1 = 168; /* Truth 1: 168 */

	CCL.LUT1CTRLC = CCL_INSEL2_TCA0_gc /* TCA0 WO2 input source */;

	CCL.LUT1CTRLB = CCL_INSEL0_SPI0_gc /* SPI0 SCK source */
	                | CCL_INSEL1_SPI0_gc /* SPI0 MOSI input source */;

	CCL.LUT1CTRLA = 0 << CCL_CLKSRC_bp       /* Clock Source Selection: disabled */
	                | CCL_EDGEDET_DIS_gc     /* Edge detector is disabled */
	                | CCL_FILTSEL_DISABLE_gc /* Filter disabled */
	                | 1 << CCL_ENABLE_bp     /* LUT Enable: enabled */
	                | 1 << CCL_OUTEN_bp;     /* Output Enable: enabled */

	CCL.CTRLA = 1 << CCL_ENABLE_bp      /* Enable: enabled */
	            | 1 << CCL_RUNSTDBY_bp; /* Run in Standby: enabled */

	return 0;
}
