#include <xc.h>
    //setting TX/RX

char mystring[20];
int lenStr = 0;

void UART_Initialize() {
           
    /*       TODObasic   
           Serial Setting      
        1.   Setting Baud rate
        2.   choose sync/async mode 
        3.   enable Serial port (configures RX/DT and TX/CK pins as serial port pins)
        3.5  enable Tx, Rx Interrupt(optional)
        4.   Enable Tx & RX*/
           
    TRISCbits.TRISC6 = 1;
    TRISCbits.TRISC7 = 1;

    //  Setting baud rate =300  4M 1200  0 0 0 51 125k 0 0 1 25
    TXSTAbits.SYNC = 0; // asy=>0, sy=>1
    BAUDCONbits.BRG16 = 0;
    TXSTAbits.BRGH = 1;
    SPBRG = 25; // change value accrodind to problem, look TA's table, baud rate =1200
    // ?FOSC??????????????setting.c??????4MHz

    //   Serial enable
    RCSTAbits.SPEN = 1; // enable asynchronous serial port
    PIR1bits.TXIF = 1;  // set when TXREG is empty(?????data????)
    PIR1bits.RCIF = 0;  // if is set, represent it is dealing with data
    TXSTAbits.TXEN = 1; // enable transition
    RCSTAbits.CREN = 1; // continuous receive, if error=>set 0
    PIE1bits.TXIE = 0;  // Transmit Interrupt Enable bit, if 0=>busy waiting
    IPR1bits.TXIP = 0;  // Transmit Interrupt Priority bit, 0=>low priority
    PIE1bits.RCIE = 1;  // Receive Interrupt Enable bit
    IPR1bits.RCIP = 0;  // T Receive Interrupt Priority bit, 0=>low priority
}

void UART_Write(unsigned char data)  // Output on Terminal
{
    while(!TXSTAbits.TRMT);
    TXREG = data;              //write to TXREG will send data 
}


void UART_Write_Text(char* text) { // Output on Terminal, limit:10 chars
    for(int i=0;text[i]!='\0';i++)
        UART_Write(text[i]);
}

void ClearBuffer(){
    for(int i = 0; i < 10 ; i++)
        mystring[i] = '\0';
    lenStr = 0;
}

void MyusartRead()
{
     /* TODObasic: try to use UART_Write to finish this function */
    mystring[lenStr] = RCREG; // read data from RCREG register
    UART_Write(mystring[lenStr]);
    if (mystring[lenStr] == '\r')
    {
        UART_Write('\n');
        
    }
    else
    {
        lenStr++;
        lenStr %= 10; // only use 10 locations
    }
    return ;
}

char *GetString(){
    return mystring;
}


// void interrupt low_priority Lo_ISR(void)
void __interrupt(low_priority)  Lo_ISR(void)
{
    if(RCIF)
    {
        if(RCSTAbits.OERR)
        {
            CREN = 0;
            Nop();
            CREN = 1;
        }
        
        MyusartRead();
    }
    
   // process other interrupt sources here, if required
    return;
}