/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */
    
    /* Setup analog functionality and port direction */
    
    // ======= ADC config =======
    // Turn off ADC
    ADCON0bits.ADON = 0;
    
    // Use Vss as Vref-
    ADCON1bits.VCFG1 = 0;
    
    // Use Vdd as Vref+
    ADCON1bits.VCFG0 = 0;
    
    // Right justify the result
    // www.settorezero.com/wordpress/contents/2010/03/convertitore_AD_04-giustificazione_risultato.gif
    ADCON2bits.ADFM = 1;
    //REMEMBER! To use the result, we must do this before:
    // int value;
    // value = ADRESL + (ADRESH << 8);
    
    // Use an acquisition time of 6 TAD
    ADCON2bits.ACQT = 011;
    
    // Use an A/D clock that's 8TOSC, valid until 10MHz
    // it's ok since we work at 8MHz
    // page 267 datasheet of PIC18F4550
    ADCON2bits.ADCS = 001;
    // ======= End ADC config =======
    
    // ======= PORTA config =======
    // Set RA0...RA3 as digital input
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA3 = 1;
    
    // Select AN0...AN3 as analog, the rest as digital
    ADCON1bits.PCFG = 0b1011;
    // ======= End PORTA config =======
    
    
    /* Initialize peripherals */

    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */

    /* Enable interrupts */
}

