#include "setting_hardaware/setting.h"
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
// using namespace std;
#define _XTAL_FREQ 125000
char str[20];


void main(void) 
{
    unsigned char number[] = {0xf7, 0x24, 0xdd, 0xed, 0x2e, 0x6b, 0xfb, 0x25, 0xff, 0x6f};
    int emergency = 0;
    SYSTEM_Initialize() ;
    int count = 0;
    TRISD = 0;
    LATD = 0; //emergency light
    LATA = 0; //seven 
    TRISA = 0;
    TRISE = 0; //red green light
    LATE = 1; //red RE0 yellow RE1  green RE2
    PORTB = 0;  // RB0=emergency RB2 train start RB1 test if train left
    int normal =1;
    TRISB = 0b00000111;
    while(1) {
        
        if (CCPR1L == 0x04 && CCP1CONbits.DC1B == 0b00){ 
            count++;
            normal = 0;
                if(emergency == 1){
                    LATD=0b00001111;
                }else if(count%2==1){
                    LATD=0b00000101;
                }else{
                    LATD=0b00001010;
            }
            __delay_ms(100);
        }
        if (CCPR1L == 0x0B && CCP1CONbits.DC1B == 0b11){ 
            LATD=0b00000000;
        }
        
        if (PORTBbits.RB1 == 0) //train left
        {
            LATE = 4;
            LATA = 0;
            UART_Write_Text("stop\n\r");
            normal = 1;
            count=0;
            while (1)
            {
                for (int i = 0; i < 25; i++);
                count++;
                if(count%2==1){
                    LATD=0b00000101;
                }else{
                    LATD=0b00001010;
                }
                if (CCPR1L == 0x0B && CCP1CONbits.DC1B == 0b11){ 
                    break;
                }else if (CCP1CONbits.DC1B < 0b11)
                    CCP1CONbits.DC1B++;
                else
                {
                    CCPR1L++;
                    CCP1CONbits.DC1B = 0b00;
                }
                __delay_ms(100); 
            }
        }
        else if(PORTBbits.RB0 == 0){  //train  start
            LATE = 1;
            LATA = 0;
            normal = 0;
            UART_Write_Text("start\n\r");
            count=0;
            while(1){
                count++;
                if(count%2==1){
                    LATD=0b00000101;
                }else{
                    LATD=0b00001010;
                }
                if (CCPR1L == 0x04 && CCP1CONbits.DC1B == 0b00){
                    break;
                }else if (CCP1CONbits.DC1B > 0b00)
                    CCP1CONbits.DC1B --;
                else
                {
                    CCPR1L--;
                    CCP1CONbits.DC1B = 0b11;
                }
                __delay_ms(100);
            }
        }
        else if(PORTBbits.RB0 == 0){ //emergency
            LATE = 1;
            LATA = 0;
            count=0;
            if(emergency == 0){
                UART_Write_Text("emergency\n\r");
            }
            while (1)
            {
                normal = 0;
                LATD=0b00001111;
                for (int i = 0; i < 25; i++);
                if(emergency == 1){
                    if (CCPR1L == 0x0B && CCP1CONbits.DC1B == 0b11){
                        emergency = 0;
                        UART_Write_Text("emergency off\n\r");
                        normal = 1;
                        LATE = 4;
                        break;
                    }else if (CCP1CONbits.DC1B < 0b11)
                        CCP1CONbits.DC1B++;
                    else
                    {
                        CCPR1L++;
                        CCP1CONbits.DC1B = 0b00;
                    }
                    __delay_ms(100);
                }
                if(emergency == 0){
                    
                    if (CCPR1L == 0x04 && CCP1CONbits.DC1B == 0b00){
                        emergency = 1;
                        break;
                    }else if (CCP1CONbits.DC1B > 0b00)
                        CCP1CONbits.DC1B --;
                    else
                    {
                        CCPR1L--;
                        CCP1CONbits.DC1B = 0b11;
                    }
                    __delay_ms(100);
                }
            }
        }else if(normal == 1){ // red green light
            if(LATE == 1){ //red
                for(int i = 9;i > 0; i--){
                    LATA = number[i];
                    __delay_ms(800);
                    if(PORTBbits.RB0 == 0 || PORTBbits.RB2 == 0){
                        LATE = 0;
                        normal = 0;
                        break;
                    }
                   
                }
                LATE = 2;
            }else if(LATE == 2){ //yellow
                for(int i = 4;i > 0; i--){
                    LATA = number[i];
                    __delay_ms(800);
                    if(PORTBbits.RB0 == 0 || PORTBbits.RB2 == 0){
                        LATE = 0;
                        normal = 0;
                        break;
                    }
                }
                LATE = 4;
            }else if(LATE ==4){ //green
                for(int i = 9;i > 0; i--){
                    LATA = number[i];
                    __delay_ms(800);
                    if(PORTBbits.RB0 == 0 || PORTBbits.RB2 == 0){
                        LATE = 0;
                        normal = 0;
                        break;
                    }
                }
                LATE = 1;
            }
        }
        
    }
    return;
}

void __interrupt(high_priority) Hi_ISR(void)
{

}