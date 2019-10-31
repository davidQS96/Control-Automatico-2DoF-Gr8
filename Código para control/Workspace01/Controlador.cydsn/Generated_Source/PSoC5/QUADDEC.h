/*******************************************************************************
* File Name: QUADDEC.h  
* Version 3.0
*
* Description:
*  This file provides constants and parameter values for the Quadrature
*  Decoder component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_QUADRATURE_DECODER_QUADDEC_H)
#define CY_QUADRATURE_DECODER_QUADDEC_H

#include "cyfitter.h"
#include "CyLib.h"
#include "cytypes.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component QuadDec_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#define QUADDEC_COUNTER_SIZE               (16u)
#define QUADDEC_COUNTER_SIZE_8_BIT         (8u)
#define QUADDEC_COUNTER_SIZE_16_BIT        (16u)
#define QUADDEC_COUNTER_SIZE_32_BIT        (32u)

#if (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_8_BIT)
    #include "QUADDEC_Cnt8.h"
#else 
    /* (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_16_BIT) || 
    *  (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT) 
    */
    #include "QUADDEC_Cnt16.h"
#endif /* QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_8_BIT */

extern uint8 QUADDEC_initVar;


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define QUADDEC_COUNTER_RESOLUTION         (4u)


/***************************************
*       Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} QUADDEC_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  QUADDEC_Init(void) ;
void  QUADDEC_Start(void) ;
void  QUADDEC_Stop(void) ;
void  QUADDEC_Enable(void) ;
uint8 QUADDEC_GetEvents(void) ;
void  QUADDEC_SetInterruptMask(uint8 mask) ;
uint8 QUADDEC_GetInterruptMask(void) ;
int16 QUADDEC_GetCounter(void) ;
void  QUADDEC_SetCounter(int16 value)
;
void  QUADDEC_Sleep(void) ;
void  QUADDEC_Wakeup(void) ;
void  QUADDEC_SaveConfig(void) ;
void  QUADDEC_RestoreConfig(void) ;

#if (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT)
    CY_ISR_PROTO(QUADDEC_ISR);
#endif /* QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT */


/***************************************
*           API Constants
***************************************/

#if (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT)
    #define QUADDEC_ISR_NUMBER             ((uint8) QUADDEC_isr__INTC_NUMBER)
    #define QUADDEC_ISR_PRIORITY           ((uint8) QUADDEC_isr__INTC_PRIOR_NUM)
#endif /* QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT */


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define QUADDEC_GLITCH_FILTERING           (1u)
#define QUADDEC_INDEX_INPUT                (0u)


/***************************************
*    Initial Parameter Constants
***************************************/

#if (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_8_BIT)
    #define QUADDEC_COUNTER_INIT_VALUE    (0x80u)
#else 
    /* (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_16_BIT) ||
    *  (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT)
    */
    #define QUADDEC_COUNTER_INIT_VALUE    (0x8000u)
    #define QUADDEC_COUNTER_MAX_VALUE     (0x7FFFu)
#endif /* QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_8_BIT */


/***************************************
*             Registers
***************************************/

#define QUADDEC_STATUS_REG                 (* (reg8 *) QUADDEC_bQuadDec_Stsreg__STATUS_REG)
#define QUADDEC_STATUS_PTR                 (  (reg8 *) QUADDEC_bQuadDec_Stsreg__STATUS_REG)
#define QUADDEC_STATUS_MASK                (* (reg8 *) QUADDEC_bQuadDec_Stsreg__MASK_REG)
#define QUADDEC_STATUS_MASK_PTR            (  (reg8 *) QUADDEC_bQuadDec_Stsreg__MASK_REG)
#define QUADDEC_SR_AUX_CONTROL             (* (reg8 *) QUADDEC_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)
#define QUADDEC_SR_AUX_CONTROL_PTR         (  (reg8 *) QUADDEC_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)


/***************************************
*        Register Constants
***************************************/

#define QUADDEC_COUNTER_OVERFLOW_SHIFT     (0x00u)
#define QUADDEC_COUNTER_UNDERFLOW_SHIFT    (0x01u)
#define QUADDEC_COUNTER_RESET_SHIFT        (0x02u)
#define QUADDEC_INVALID_IN_SHIFT           (0x03u)
#define QUADDEC_COUNTER_OVERFLOW           ((uint8) (0x01u << QUADDEC_COUNTER_OVERFLOW_SHIFT))
#define QUADDEC_COUNTER_UNDERFLOW          ((uint8) (0x01u << QUADDEC_COUNTER_UNDERFLOW_SHIFT))
#define QUADDEC_COUNTER_RESET              ((uint8) (0x01u << QUADDEC_COUNTER_RESET_SHIFT))
#define QUADDEC_INVALID_IN                 ((uint8) (0x01u << QUADDEC_INVALID_IN_SHIFT))

#define QUADDEC_INTERRUPTS_ENABLE_SHIFT    (0x04u)
#define QUADDEC_INTERRUPTS_ENABLE          ((uint8)(0x01u << QUADDEC_INTERRUPTS_ENABLE_SHIFT))
#define QUADDEC_INIT_INT_MASK              (0x0Fu)


/******************************************************************************************
* Following code are OBSOLETE and must not be used starting from Quadrature Decoder 2.20
******************************************************************************************/
#define QUADDEC_DISABLE                    (0x00u)


#endif /* CY_QUADRATURE_DECODER_QUADDEC_H */


/* [] END OF FILE */
