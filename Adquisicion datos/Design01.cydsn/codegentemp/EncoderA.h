/*******************************************************************************
* File Name: EncoderA.h  
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

#if !defined(CY_PINS_EncoderA_H) /* Pins EncoderA_H */
#define CY_PINS_EncoderA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "EncoderA_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 EncoderA__PORT == 15 && ((EncoderA__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    EncoderA_Write(uint8 value);
void    EncoderA_SetDriveMode(uint8 mode);
uint8   EncoderA_ReadDataReg(void);
uint8   EncoderA_Read(void);
void    EncoderA_SetInterruptMode(uint16 position, uint16 mode);
uint8   EncoderA_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the EncoderA_SetDriveMode() function.
     *  @{
     */
        #define EncoderA_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define EncoderA_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define EncoderA_DM_RES_UP          PIN_DM_RES_UP
        #define EncoderA_DM_RES_DWN         PIN_DM_RES_DWN
        #define EncoderA_DM_OD_LO           PIN_DM_OD_LO
        #define EncoderA_DM_OD_HI           PIN_DM_OD_HI
        #define EncoderA_DM_STRONG          PIN_DM_STRONG
        #define EncoderA_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define EncoderA_MASK               EncoderA__MASK
#define EncoderA_SHIFT              EncoderA__SHIFT
#define EncoderA_WIDTH              1u

/* Interrupt constants */
#if defined(EncoderA__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in EncoderA_SetInterruptMode() function.
     *  @{
     */
        #define EncoderA_INTR_NONE      (uint16)(0x0000u)
        #define EncoderA_INTR_RISING    (uint16)(0x0001u)
        #define EncoderA_INTR_FALLING   (uint16)(0x0002u)
        #define EncoderA_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define EncoderA_INTR_MASK      (0x01u) 
#endif /* (EncoderA__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define EncoderA_PS                     (* (reg8 *) EncoderA__PS)
/* Data Register */
#define EncoderA_DR                     (* (reg8 *) EncoderA__DR)
/* Port Number */
#define EncoderA_PRT_NUM                (* (reg8 *) EncoderA__PRT) 
/* Connect to Analog Globals */                                                  
#define EncoderA_AG                     (* (reg8 *) EncoderA__AG)                       
/* Analog MUX bux enable */
#define EncoderA_AMUX                   (* (reg8 *) EncoderA__AMUX) 
/* Bidirectional Enable */                                                        
#define EncoderA_BIE                    (* (reg8 *) EncoderA__BIE)
/* Bit-mask for Aliased Register Access */
#define EncoderA_BIT_MASK               (* (reg8 *) EncoderA__BIT_MASK)
/* Bypass Enable */
#define EncoderA_BYP                    (* (reg8 *) EncoderA__BYP)
/* Port wide control signals */                                                   
#define EncoderA_CTL                    (* (reg8 *) EncoderA__CTL)
/* Drive Modes */
#define EncoderA_DM0                    (* (reg8 *) EncoderA__DM0) 
#define EncoderA_DM1                    (* (reg8 *) EncoderA__DM1)
#define EncoderA_DM2                    (* (reg8 *) EncoderA__DM2) 
/* Input Buffer Disable Override */
#define EncoderA_INP_DIS                (* (reg8 *) EncoderA__INP_DIS)
/* LCD Common or Segment Drive */
#define EncoderA_LCD_COM_SEG            (* (reg8 *) EncoderA__LCD_COM_SEG)
/* Enable Segment LCD */
#define EncoderA_LCD_EN                 (* (reg8 *) EncoderA__LCD_EN)
/* Slew Rate Control */
#define EncoderA_SLW                    (* (reg8 *) EncoderA__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define EncoderA_PRTDSI__CAPS_SEL       (* (reg8 *) EncoderA__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define EncoderA_PRTDSI__DBL_SYNC_IN    (* (reg8 *) EncoderA__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define EncoderA_PRTDSI__OE_SEL0        (* (reg8 *) EncoderA__PRTDSI__OE_SEL0) 
#define EncoderA_PRTDSI__OE_SEL1        (* (reg8 *) EncoderA__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define EncoderA_PRTDSI__OUT_SEL0       (* (reg8 *) EncoderA__PRTDSI__OUT_SEL0) 
#define EncoderA_PRTDSI__OUT_SEL1       (* (reg8 *) EncoderA__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define EncoderA_PRTDSI__SYNC_OUT       (* (reg8 *) EncoderA__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(EncoderA__SIO_CFG)
    #define EncoderA_SIO_HYST_EN        (* (reg8 *) EncoderA__SIO_HYST_EN)
    #define EncoderA_SIO_REG_HIFREQ     (* (reg8 *) EncoderA__SIO_REG_HIFREQ)
    #define EncoderA_SIO_CFG            (* (reg8 *) EncoderA__SIO_CFG)
    #define EncoderA_SIO_DIFF           (* (reg8 *) EncoderA__SIO_DIFF)
#endif /* (EncoderA__SIO_CFG) */

/* Interrupt Registers */
#if defined(EncoderA__INTSTAT)
    #define EncoderA_INTSTAT            (* (reg8 *) EncoderA__INTSTAT)
    #define EncoderA_SNAP               (* (reg8 *) EncoderA__SNAP)
    
	#define EncoderA_0_INTTYPE_REG 		(* (reg8 *) EncoderA__0__INTTYPE)
#endif /* (EncoderA__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_EncoderA_H */


/* [] END OF FILE */
