/*******************************************************************************
* File Name: EncoderB.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_EncoderB_H) /* Pins EncoderB_H */
#define CY_PINS_EncoderB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "EncoderB_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 EncoderB__PORT == 15 && ((EncoderB__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    EncoderB_Write(uint8 value);
void    EncoderB_SetDriveMode(uint8 mode);
uint8   EncoderB_ReadDataReg(void);
uint8   EncoderB_Read(void);
void    EncoderB_SetInterruptMode(uint16 position, uint16 mode);
uint8   EncoderB_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the EncoderB_SetDriveMode() function.
     *  @{
     */
        #define EncoderB_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define EncoderB_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define EncoderB_DM_RES_UP          PIN_DM_RES_UP
        #define EncoderB_DM_RES_DWN         PIN_DM_RES_DWN
        #define EncoderB_DM_OD_LO           PIN_DM_OD_LO
        #define EncoderB_DM_OD_HI           PIN_DM_OD_HI
        #define EncoderB_DM_STRONG          PIN_DM_STRONG
        #define EncoderB_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define EncoderB_MASK               EncoderB__MASK
#define EncoderB_SHIFT              EncoderB__SHIFT
#define EncoderB_WIDTH              1u

/* Interrupt constants */
#if defined(EncoderB__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in EncoderB_SetInterruptMode() function.
     *  @{
     */
        #define EncoderB_INTR_NONE      (uint16)(0x0000u)
        #define EncoderB_INTR_RISING    (uint16)(0x0001u)
        #define EncoderB_INTR_FALLING   (uint16)(0x0002u)
        #define EncoderB_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define EncoderB_INTR_MASK      (0x01u) 
#endif /* (EncoderB__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define EncoderB_PS                     (* (reg8 *) EncoderB__PS)
/* Data Register */
#define EncoderB_DR                     (* (reg8 *) EncoderB__DR)
/* Port Number */
#define EncoderB_PRT_NUM                (* (reg8 *) EncoderB__PRT) 
/* Connect to Analog Globals */                                                  
#define EncoderB_AG                     (* (reg8 *) EncoderB__AG)                       
/* Analog MUX bux enable */
#define EncoderB_AMUX                   (* (reg8 *) EncoderB__AMUX) 
/* Bidirectional Enable */                                                        
#define EncoderB_BIE                    (* (reg8 *) EncoderB__BIE)
/* Bit-mask for Aliased Register Access */
#define EncoderB_BIT_MASK               (* (reg8 *) EncoderB__BIT_MASK)
/* Bypass Enable */
#define EncoderB_BYP                    (* (reg8 *) EncoderB__BYP)
/* Port wide control signals */                                                   
#define EncoderB_CTL                    (* (reg8 *) EncoderB__CTL)
/* Drive Modes */
#define EncoderB_DM0                    (* (reg8 *) EncoderB__DM0) 
#define EncoderB_DM1                    (* (reg8 *) EncoderB__DM1)
#define EncoderB_DM2                    (* (reg8 *) EncoderB__DM2) 
/* Input Buffer Disable Override */
#define EncoderB_INP_DIS                (* (reg8 *) EncoderB__INP_DIS)
/* LCD Common or Segment Drive */
#define EncoderB_LCD_COM_SEG            (* (reg8 *) EncoderB__LCD_COM_SEG)
/* Enable Segment LCD */
#define EncoderB_LCD_EN                 (* (reg8 *) EncoderB__LCD_EN)
/* Slew Rate Control */
#define EncoderB_SLW                    (* (reg8 *) EncoderB__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define EncoderB_PRTDSI__CAPS_SEL       (* (reg8 *) EncoderB__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define EncoderB_PRTDSI__DBL_SYNC_IN    (* (reg8 *) EncoderB__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define EncoderB_PRTDSI__OE_SEL0        (* (reg8 *) EncoderB__PRTDSI__OE_SEL0) 
#define EncoderB_PRTDSI__OE_SEL1        (* (reg8 *) EncoderB__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define EncoderB_PRTDSI__OUT_SEL0       (* (reg8 *) EncoderB__PRTDSI__OUT_SEL0) 
#define EncoderB_PRTDSI__OUT_SEL1       (* (reg8 *) EncoderB__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define EncoderB_PRTDSI__SYNC_OUT       (* (reg8 *) EncoderB__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(EncoderB__SIO_CFG)
    #define EncoderB_SIO_HYST_EN        (* (reg8 *) EncoderB__SIO_HYST_EN)
    #define EncoderB_SIO_REG_HIFREQ     (* (reg8 *) EncoderB__SIO_REG_HIFREQ)
    #define EncoderB_SIO_CFG            (* (reg8 *) EncoderB__SIO_CFG)
    #define EncoderB_SIO_DIFF           (* (reg8 *) EncoderB__SIO_DIFF)
#endif /* (EncoderB__SIO_CFG) */

/* Interrupt Registers */
#if defined(EncoderB__INTSTAT)
    #define EncoderB_INTSTAT            (* (reg8 *) EncoderB__INTSTAT)
    #define EncoderB_SNAP               (* (reg8 *) EncoderB__SNAP)
    
	#define EncoderB_0_INTTYPE_REG 		(* (reg8 *) EncoderB__0__INTTYPE)
#endif /* (EncoderB__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_EncoderB_H */


/* [] END OF FILE */
