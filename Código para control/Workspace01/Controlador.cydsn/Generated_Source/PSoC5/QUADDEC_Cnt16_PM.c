/*******************************************************************************
* File Name: QUADDEC_Cnt16_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "QUADDEC_Cnt16.h"

static QUADDEC_Cnt16_backupStruct QUADDEC_Cnt16_backup;


/*******************************************************************************
* Function Name: QUADDEC_Cnt16_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  QUADDEC_Cnt16_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void QUADDEC_Cnt16_SaveConfig(void) 
{
    #if (!QUADDEC_Cnt16_UsingFixedFunction)

        QUADDEC_Cnt16_backup.CounterUdb = QUADDEC_Cnt16_ReadCounter();

        #if(!QUADDEC_Cnt16_ControlRegRemoved)
            QUADDEC_Cnt16_backup.CounterControlRegister = QUADDEC_Cnt16_ReadControlRegister();
        #endif /* (!QUADDEC_Cnt16_ControlRegRemoved) */

    #endif /* (!QUADDEC_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QUADDEC_Cnt16_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  QUADDEC_Cnt16_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void QUADDEC_Cnt16_RestoreConfig(void) 
{      
    #if (!QUADDEC_Cnt16_UsingFixedFunction)

       QUADDEC_Cnt16_WriteCounter(QUADDEC_Cnt16_backup.CounterUdb);

        #if(!QUADDEC_Cnt16_ControlRegRemoved)
            QUADDEC_Cnt16_WriteControlRegister(QUADDEC_Cnt16_backup.CounterControlRegister);
        #endif /* (!QUADDEC_Cnt16_ControlRegRemoved) */

    #endif /* (!QUADDEC_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QUADDEC_Cnt16_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  QUADDEC_Cnt16_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void QUADDEC_Cnt16_Sleep(void) 
{
    #if(!QUADDEC_Cnt16_ControlRegRemoved)
        /* Save Counter's enable state */
        if(QUADDEC_Cnt16_CTRL_ENABLE == (QUADDEC_Cnt16_CONTROL & QUADDEC_Cnt16_CTRL_ENABLE))
        {
            /* Counter is enabled */
            QUADDEC_Cnt16_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            QUADDEC_Cnt16_backup.CounterEnableState = 0u;
        }
    #else
        QUADDEC_Cnt16_backup.CounterEnableState = 1u;
        if(QUADDEC_Cnt16_backup.CounterEnableState != 0u)
        {
            QUADDEC_Cnt16_backup.CounterEnableState = 0u;
        }
    #endif /* (!QUADDEC_Cnt16_ControlRegRemoved) */
    
    QUADDEC_Cnt16_Stop();
    QUADDEC_Cnt16_SaveConfig();
}


/*******************************************************************************
* Function Name: QUADDEC_Cnt16_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  QUADDEC_Cnt16_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void QUADDEC_Cnt16_Wakeup(void) 
{
    QUADDEC_Cnt16_RestoreConfig();
    #if(!QUADDEC_Cnt16_ControlRegRemoved)
        if(QUADDEC_Cnt16_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            QUADDEC_Cnt16_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!QUADDEC_Cnt16_ControlRegRemoved) */
    
}


/* [] END OF FILE */
