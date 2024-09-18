#include <xc.h>

void CCP1_Initialize() {
    TRISCbits.TRISC2=0;	// RC2 pin is output.
    //CCP1CON=9;		// Compare mode, initialize CCP1 pin high, clear output on compare match
    //PIR1bits.CCP1IF=0;
    //IPR1bits.CCP1IP = 1;
    T2CONbits.TMR2ON = 0b1;
    T2CONbits.T2CKPS = 0b01;
    CCP1CONbits.CCP1M = 0b1100;
    //OSCCONbits.IRCF = 0b001;
    LATC = 0;
    PR2 = 0x9b;
    CCPR1L = 0X0B;
    CCP1CONbits.DC1B = 0b11;
}
