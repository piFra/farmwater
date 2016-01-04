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

void configInterrupts(void)
{
    // Disable all interrupts
    INTCONbits.GIE = 0;
    
    // Disable peripheral interrupts too
    INTCONbits.PEIE = 0;
    
    // Enable INT0 interrupts
    INTCONbits.INT0E = 1;

    // Enable TMR0 interrupts
    INTCONbits.TMR0IE = 1;

    // Enable RB Port change interrupt
    INTCONbits.RBIE = 1;
    
    // Disable RB pullup resistors
    INTCON2bits.RBPU = 1;
    
    // Enable the A/D interrupt
    PIE1bits.ADIE = 1;
    
    // Enable the TMR1 interrupt
    PIE1bits.TMR1IE = 1;
    
    // Enable the TMR3 interrupt
    PIE2bits.TMR3IE = 1;
    
    // Disable interrupt priority
    RCONbits.IPEN = 0;
    
    // Disable at ALL the WatchDog timer
    // http://microchip.wikidot.com/8bit:wdt
    WDTCONbits.SWDTEN = 0;

    // Enable peripheral interrupts too
    INTCONbits.PEIE = 1;
    
    // Enable all interrupts
    INTCONbits.GIE = 1;
}

void initADC(void)
{
    // ======= ADC config =======
    // Turn off ADC
    ADCON0bits.ADON = 0;

    // Select AN0...AN3 as analog, the rest as digital
    ADCON1bits.PCFG = 0b1011;
    
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
    ADCON2bits.ACQT = 0b011;
    
    // Use an A/D clock that's 8TOSC, valid until 10MHz
    // it's ok since we work at 8MHz
    // page 267 datasheet of PIC18F4550
    ADCON2bits.ADCS = 0b001;
    
    // Turn on the ADC module
    ADCON0bits.ADON = 1;
    // ======= End ADC config =======
}

void InitApp(void)
{   
    configInterrupts();
    initPORTS();
    initADC();
    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */
    
    
    /* Enable interrupts */
}

void initPORTS(void)
{
    // ======= PORTA config =======
    // Set RA0...RA3 as digital input
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA3 = 1;
    
    // Set RA4..RA7 as input, even if they are not used 
    TRISAbits.TRISA4 = 1;
    TRISAbits.TRISA5 = 1;
    TRISAbits.TRISA6 = 1;
    // ======= End PORTA config =======
    
    // ======= PORTB config =======
    // Set RB0...RB7 as input
    TRISB = 0xFF;
    // ======= End PORTB config =======

    // ======= PORTD config =======
    // Set RD0...RD7 as output
    TRISD = 0x00;
    // ======= End PORTD config =======

    // ======= PORTE config =======
    // Set RE0...RE2 as output even if RE2 is not used
    TRISE = 0x00;
    // ======= End PORTE config =======

    // ======= PORTC config =======
    // Set RC0...RC3 as output
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC3 = 0;
    
    // RC6 and RC7 will also be configured as UART TX and UART RX in initUART()
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 1;
    // ======= End PORTC config =======
}