/*******************************************************************************
* File Name: QUADDEC_PM.c
* Version 3.0
*
* Description:
*  This file contains the setup, control and status commands to support 
*  component operations in low power mode.  
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

static QUADDEC_BACKUP_STRUCT QUADDEC_backup = {0u};


/*******************************************************************************
* Function Name: QUADDEC_SaveConfig
********************************************************************************
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QUADDEC_SaveConfig(void) 
{
    #if (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_8_BIT)
        QUADDEC_Cnt8_SaveConfig();
    #else 
        /* (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_16_BIT) || 
         * (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT)
         */
        QUADDEC_Cnt16_SaveConfig();
    #endif /* (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: QUADDEC_RestoreConfig
********************************************************************************
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void QUADDEC_RestoreConfig(void) 
{
    #if (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_8_BIT)
        QUADDEC_Cnt8_RestoreConfig();
    #else 
        /* (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_16_BIT) || 
         * (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT) 
         */
        QUADDEC_Cnt16_RestoreConfig();
    #endif /* (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: QUADDEC_Sleep
********************************************************************************
* 
* Summary:
*  Prepare Quadrature Decoder Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QUADDEC_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void QUADDEC_Sleep(void) 
{
    if (0u != (QUADDEC_SR_AUX_CONTROL & QUADDEC_INTERRUPTS_ENABLE))
    {
        QUADDEC_backup.enableState = 1u;
    }
    else /* The Quadrature Decoder Component is disabled */
    {
        QUADDEC_backup.enableState = 0u;
    }

    QUADDEC_Stop();
    QUADDEC_SaveConfig();
}


/*******************************************************************************
* Function Name: QUADDEC_Wakeup
********************************************************************************
*
* Summary:
*  Prepare Quadrature Decoder Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  QUADDEC_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void QUADDEC_Wakeup(void) 
{
    QUADDEC_RestoreConfig();

    if (QUADDEC_backup.enableState != 0u)
    {
        #if (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_8_BIT)
            QUADDEC_Cnt8_Enable();
        #else 
            /* (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_16_BIT) || 
            *  (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_32_BIT) 
            */
            QUADDEC_Cnt16_Enable();
        #endif /* (QUADDEC_COUNTER_SIZE == QUADDEC_COUNTER_SIZE_8_BIT) */

        /* Enable component's operation */
        QUADDEC_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */

