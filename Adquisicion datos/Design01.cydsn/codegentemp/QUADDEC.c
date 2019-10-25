/*******************************************************************************
* File Name: QUADDEC.c  
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the Quadrature Decoder
*  component.
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

#include "QUADDEC.h"

#if (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT)
    #include "QUADDEC_PVT.h"
#endif /* QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT */

uint8 QUADDEC_initVar = 0u;


/*******************************************************************************
* Function Name: QUADDEC_Init
********************************************************************************
*
* Summary:
*  Inits/Restores default QuadDec configuration provided with customizer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QUADDEC_Init(void) 
{
    #if (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT)
        /* Disable Interrupt. */
        CyIntDisable(QUADDEC_ISR_NUMBER);
        /* Set the ISR to point to the QUADDEC_isr Interrupt. */
        (void) CyIntSetVector(QUADDEC_ISR_NUMBER, & QUADDEC_ISR);
        /* Set the priority. */
        CyIntSetPriority(QUADDEC_ISR_NUMBER, QUADDEC_ISR_PRIORITY);
    #endif /* QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: QUADDEC_Enable
********************************************************************************
*
* Summary:
*  This function enable interrupts from Component and also enable Component's
*  ISR in case of 32-bit counter.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QUADDEC_Enable(void) 
{
    uint8 enableInterrupts;

    QUADDEC_SetInterruptMask(QUADDEC_INIT_INT_MASK);

    /* Clear pending interrupts. */
    (void) QUADDEC_GetEvents();
    
    enableInterrupts = CyEnterCriticalSection();

    /* Enable interrupts from Statusi register */
    QUADDEC_SR_AUX_CONTROL |= QUADDEC_INTERRUPTS_ENABLE;

    CyExitCriticalSection(enableInterrupts);        

    #if (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT)
        /* Enable Component interrupts */
        CyIntEnable(QUADDEC_ISR_NUMBER);
    #endif /* QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: QUADDEC_Start
********************************************************************************
*
* Summary:
*  Initializes UDBs and other relevant hardware.
*  Resets counter, enables or disables all relevant interrupts.
*  Starts monitoring the inputs and counting.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  QUADDEC_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QUADDEC_Start(void) 
{
    #if (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_8_BIT)
        QUADDEC_Cnt8_Start();
        QUADDEC_Cnt8_WriteCounter(QUADDEC_COUNTER_INIT_VALUE);
    #else
        /* (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_16_BIT) || 
        *  (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT) 
        */
        QUADDEC_Cnt16_Start();
        QUADDEC_Cnt16_WriteCounter(QUADDEC_COUNTER_INIT_VALUE);
    #endif /* QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_8_BIT */
    
    #if (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT)        
       QUADDEC_count32SoftPart = 0;
    #endif /* QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT */

    if (QUADDEC_initVar == 0u)
    {
        QUADDEC_Init();
        QUADDEC_initVar = 1u;
    }

    QUADDEC_Enable();
}


/*******************************************************************************
* Function Name: QUADDEC_Stop
********************************************************************************
*
* Summary:
*  Turns off UDBs and other relevant hardware.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QUADDEC_Stop(void) 
{
    uint8 enableInterrupts;

    #if (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_8_BIT)
        QUADDEC_Cnt8_Stop();
    #else 
        /* (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_16_BIT) ||
        *  (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT)
        */
        QUADDEC_Cnt16_Stop();    /* counter disable */
    #endif /* (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_8_BIT) */
 
    enableInterrupts = CyEnterCriticalSection();

    /* Disable interrupts interrupts from Statusi register */
    QUADDEC_SR_AUX_CONTROL &= (uint8) (~QUADDEC_INTERRUPTS_ENABLE);

    CyExitCriticalSection(enableInterrupts);

    #if (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT)
        CyIntDisable(QUADDEC_ISR_NUMBER);    /* interrupt disable */
    #endif /* QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: QUADDEC_GetCounter
********************************************************************************
*
* Summary:
*  Reports the current value of the counter.
*
* Parameters:
*  None.
*
* Return:
*  The counter value. Return type is signed and per the counter size setting.
*  A positive value indicates clockwise movement (B before A).
*
* Global variables:
*  QUADDEC_count32SoftPart - used to get hi 16 bit for current value
*  of the 32-bit counter, when Counter size equal 32-bit.
*
*******************************************************************************/
int16 QUADDEC_GetCounter(void) 
{
    int16 count;
    uint16 tmpCnt;

    #if (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT)
        int16 hwCount;

        CyIntDisable(QUADDEC_ISR_NUMBER);

        tmpCnt = QUADDEC_Cnt16_ReadCounter();
        hwCount = (int16) ((int32) tmpCnt - (int32) QUADDEC_COUNTER_INIT_VALUE);
        count = QUADDEC_count32SoftPart + hwCount;

        CyIntEnable(QUADDEC_ISR_NUMBER);
    #else 
        /* (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_8_BIT) || 
        *  (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_16_BIT)
        */
        #if (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_8_BIT)
            tmpCnt = QUADDEC_Cnt8_ReadCounter();
        #else /* (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_16_BIT) */
            tmpCnt = QUADDEC_Cnt16_ReadCounter();
        #endif  /* QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_8_BIT */

        count = (int16) ((int32) tmpCnt -
                (int32) QUADDEC_COUNTER_INIT_VALUE);

    #endif /* QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT */ 

    return (count);
}


/*******************************************************************************
* Function Name: QUADDEC_SetCounter
********************************************************************************
*
* Summary:
*  Sets the current value of the counter.
*
* Parameters:
*  value:  The new value. Parameter type is signed and per the counter size
*  setting.
*
* Return:
*  None.
*
* Global variables:
*  QUADDEC_count32SoftPart - modified to set hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QUADDEC_SetCounter(int16 value) 
{
    #if ((QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_8_BIT) || \
         (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_16_BIT))
        uint16 count;
        
        if (value >= 0)
        {
            count = (uint16) value + QUADDEC_COUNTER_INIT_VALUE;
        }
        else
        {
            count = QUADDEC_COUNTER_INIT_VALUE - (uint16)(-value);
        }
        #if (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_8_BIT)
            QUADDEC_Cnt8_WriteCounter(count);
        #else /* (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_16_BIT) */
            QUADDEC_Cnt16_WriteCounter(count);
        #endif  /* QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_8_BIT */
    #else /* (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT) */
        CyIntDisable(QUADDEC_ISR_NUMBER);

        QUADDEC_Cnt16_WriteCounter(QUADDEC_COUNTER_INIT_VALUE);
        QUADDEC_count32SoftPart = value;

        CyIntEnable(QUADDEC_ISR_NUMBER);
    #endif  /* (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_8_BIT) ||
             * (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_16_BIT)
             */
}


/*******************************************************************************
* Function Name: QUADDEC_GetEvents
********************************************************************************
* 
* Summary:
*   Reports the current status of events. This function clears the bits of the 
*   status register.
*
* Parameters:
*  None.
*
* Return:
*  The events, as bits in an unsigned 8-bit value:
*    Bit      Description
*     0        Counter overflow.
*     1        Counter underflow.
*     2        Counter reset due to index, if index input is used.
*     3        Invalid A, B inputs state transition.
*
*******************************************************************************/
uint8 QUADDEC_GetEvents(void) 
{
    return (QUADDEC_STATUS_REG & QUADDEC_INIT_INT_MASK);
}


/*******************************************************************************
* Function Name: QUADDEC_SetInterruptMask
********************************************************************************
*
* Summary:
*  Enables / disables interrupts due to the events.
*  For the 32-bit counter, the overflow, underflow and reset interrupts cannot
*  be disabled, these bits are ignored.
*
* Parameters:
*  mask: Enable / disable bits in an 8-bit value, where 1 enables the interrupt.
*
* Return:
*  None.
*
*******************************************************************************/
void QUADDEC_SetInterruptMask(uint8 mask) 
{
    #if (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT)
        /* Underflow, Overflow and Reset interrupts for 32-bit Counter are always enable */
        mask |= (QUADDEC_COUNTER_OVERFLOW | QUADDEC_COUNTER_UNDERFLOW |
                 QUADDEC_COUNTER_RESET);
    #endif /* QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT */

    QUADDEC_STATUS_MASK = mask;
}


/*******************************************************************************
* Function Name: QUADDEC_GetInterruptMask
********************************************************************************
*
* Summary:
*  Reports the current interrupt mask settings.
*
* Parameters:
*  None.
*
* Return:
*  Enable / disable bits in an 8-bit value, where 1 enables the interrupt.
*  For the 32-bit counter, the overflow, underflow and reset enable bits are
*  always set.
*
*******************************************************************************/
uint8 QUADDEC_GetInterruptMask(void) 
{
    return (QUADDEC_STATUS_MASK & QUADDEC_INIT_INT_MASK);
}


/* [] END OF FILE */
