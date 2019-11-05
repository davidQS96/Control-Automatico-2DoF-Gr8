/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include<stdio.h>
#include <stdlib.h>

#define MID_COUNT           (0x8000u)   /* for 16 bit counter*/
#define DELAY               (10u)       /* 10 msec */
                                        /* Delay should be more than the period 
                                        of input signal to the quadrature 
                                        decoder */
typedef enum  rotation 
{
    NO_ROTATION     = 0,
    CLOCKWISE       = 1,
    ANTI_CLOCK
    } rotation_t;
    

int main(void)
{
    
    uint16_t count      = MID_COUNT;
    uint16_t countPrev  = MID_COUNT;
    float scalingFactor = 75.0 / 3350.0;
    float angle;
    char countStr[50];
    char angleStr[50];
    
    float contador;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    float ref=30;
    float KI=1;//Constante
    float KP=2.53058;
    float KD=7.7183;
    float max_int=1;
    
    float ek; //error
    float ik=0; 
    float dk; 
    float acc; 
    float mk; 
    float posicion1=0;  //posición anterior  (ángulo)
    float posicion; //Posicion en grados
    
    /* Select direction of rotation */
    //rotation_t emulated_rotation = CLOCKWISE;
    
    __enable_irq();/* Enable global interrupts. */
        
    /* Initialize with config set in component and enable QuadDec */
    QUADDEC_Start();
    //UART_Start();
    PWM_Start();
    LCD_Start();
    Clock_1_Start();
    
    QUADDEC_GetCounter();
    
    
    for(;;)
    {
        
        count = QUADDEC_GetCounter();
        angle = count * scalingFactor;
        
//        LCD_Position(0u, 0u);
//        LCD_PrintString("Count: ");
//        
//        LCD_Position(0u, 7u);
//        
//        sprintf(countStr, "%d          ", count);
//        LCD_PrintString(countStr);
//        
//        LCD_Position(1u, 0u);
//        LCD_PrintString("Angle: ");
//        
//        LCD_Position(1u, 7u);
        
        sprintf(angleStr, "%f", angle);
        
        posicion=angle;
        
        ek=ref-posicion;
        
        ik=KI*ek+ik;
        
        dk=KD*(posicion-posicion1);
        
        acc=-KP*(ek/100)+ik-dk;
        
        mk=acc;
        
        posicion1=posicion;
        
        if(ik> max_int){
        
            ik=max_int;   
            
        }
        
        else
        
        if(ik< -max_int)
        {
        
            ik=max_int;
            
        }
        
        if(acc>65535){
        
            acc=65535;
            
        }
        
        if(ek>30)
        {
        
        PWM_WriteCompare(acc/2);
        
        }
        
        else if(ek<30){
        
        PWM_WriteCompare(3000);
            
        }
        
    }
    
    
    
}

/* [] END OF FILE */
