/*
 * File:   main.c
 * Author: gorhas
 *
 * Created on den 15 augusti 2016, 20:54
 */

//#include <xc.h>


#include <xc.h>
#include "config.h"
//#include <p18f2580.h>
#include "ecan.h"

#define LEDPin LATAbits.LATA0 //Define LEDPin as PORT D Pin 1
#define LEDTris TRISAbits.TRISA0 //Define LEDTris as TRISD Pin 1

#define RELPin1 LATBbits.LATB4  //Define LEDPin as PORT D Pin 1
#define RELTris1 TRISBbits.TRISB4 // Define LEDTris as TRISD Pin 1

#define RELPin2 LATBbits.LATB5  //Define LEDPin as PORT D Pin 1
#define RELTris2 TRISBbits.TRISB5  //Define LEDTris as TRISD Pin 1


int varv = 200;

void delayzz(void)
{              
    int i, j;
   
    for(i=0;i<200;i++)
        {
        for(j=0;j<50;j++)
        {  ; /* Well its Just a Timer */ }
    }   
}

/*
void RunTimeInitialization(void)
{
    // Must be in Config mode to change many of settings.
    ECANSetOperationMode(ECAN_OP_MODE_CONFIG);

    // Select Mode 1
    ECANSetFunctionalMode(ECAN_MODE_1);


    // Make B0 as receiver.
    ECANSetBnTxRxMode(B0, ECAN_BUFFER_RX);

    // RXB0 will receive Stadard messages only.
    ECANSetRxBnRxMode(RXB0, ECAN_RECEIVE_ALL_VALID);

    // B0 will receive Extended
    ECANSetBnRxMode(B0, ECAN_RECEIVE_ALL_VALID);

    // Link RXF0 to RXB0 and RXF1 to B0
    ECANLinkRXF0F1ToBuffer(RXB0, B0);
    ECANLinkRXF0Thru3ToMask(ECAN_RXM0, ECAN_RXM1, ECAN_RXM0, ECAN_RXM0);

    ECANSetRXF0Value(0,         ECAN_MSG_STD);
    ECANSetRXF1Value(0,         ECAN_MSG_XTD);

    ECANSetRXM0Value(0,         ECAN_MSG_STD);
    ECANSetRXM1Value(0,         ECAN_MSG_XTD);

    // Set 125kbps @ 25MHz
    ECANSetBaudRate(2, 4, 8, 8, 8);

    // Return to Normal mode to communicate.
    ECANSetOperationMode(ECAN_OP_MODE_NORMAL);
}

*/

void main(void)
{
   int olle;

   char buffer[100];
   
   char sjw, brp, phseg1, phseg2, propseg;
   
   unsigned long id;
   
   BYTE data[4];
   BYTE dataLen;
   
   ECAN_RX_MSG_FLAGS flags;
  
   
   sjw = 3;
   brp = 8;
   phseg1 = 3;
   phseg2 = 3;
   propseg = 1;
   
   


   /*
   OSCTUNEbits.PLLEN = 1;
 
  OSCTUNEbits.TUN0 = 0;
  OSCTUNEbits.TUN1 = 0;
  OSCTUNEbits.TUN2 = 0;
  OSCTUNEbits.TUN3 = 0;
  OSCTUNEbits.TUN4 = 1;
  
   */
          
   data[0] = 0x40;
   data[1] = 0x55;
   data[2] = 0x40;
   data[3] = 0x55;

/*   
   OSCTUNEbits.PLLEN = 0;
   
   OSCTUNEbits.TUN0 = 1;
   OSCTUNEbits.TUN1 = 1;
   OSCTUNEbits.TUN2 = 1;
   OSCTUNEbits.TUN3 = 1;
   OSCTUNEbits.TUN4 = 0;
  
 */ 
   
   LEDTris = 0;//Set LED Pin data direction to OUTPUT
   LEDPin = 0;//Set LED Pin
   
   RELTris1 = 0;  //Set REL Pin data direction to OUTPUT
   RELPin1 = 0;   //Set REL Pin
 
   RELTris2 = 0;  //Set REL Pin data direction to OUTPUT
   RELPin2 = 0;   //Set REL Pin
    
   
   
   //ECANSetOperationMode(ECAN_OP_MODE_CONFIG);

   //ECANSetBaudRate(sjw, brp, phseg1, phseg2, propseg)
   //ECANSetBaudRate(2, 4, 8, 8, 8);

   //ECANSetOperationMode(ECAN_OP_MODE_NORMAL);

   //ECANSetOperationMode(ECAN_INIT_MODE);
      
   
   LEDPin = 0;
   
   ECANInitialize();
   
   data[0] = 0;
   
   while(1)
   {
        
      delayzz();
      
      data[0]++;
      
      LEDPin = ~LEDPin;
      
      //RELPin1 = ~RELPin1;
      //RELPin2 = ~RELPin2;
      
      
      //while( !ECANSendMessage(0x123, data, 4, ECAN_TX_STD_FRAME) );
      ECANSendMessage(0x42, data, 4, ECAN_TX_STD_FRAME);

     
      ECANReceiveMessage( &id,
                        data,
                        &dataLen,
                        &flags);
      
      //varv = data[1];

      if( id == 0x02)
      {
          
      while(data[0] != 0x00)
      {
        //LEDPin = ~LEDPin;
          
           LEDPin = 1;//Set LED Pin
           RELPin1 = 1;
           RELPin2 = 0;
           
          delayzz();
           LEDPin = 0;//Set LED Pin
           RELPin1 = 0;
           RELPin2 = 1;
           
          delayzz();

          data[0]--;
      
          ECANSendMessage(0x42, data, 4, ECAN_TX_STD_FRAME);
          
        }
      }
     
      
       
    //LEDPin = 0;//Set LED Pin
    
    id = 0x00;
    
    
      //data[0] = 0;
      
   
    }
   
    return;
}
