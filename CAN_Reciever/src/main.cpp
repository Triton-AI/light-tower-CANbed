/*
  This code builds upon the reciever library fron Longan labs
  A connection is established with the serial monitor for observation
  This will enable the CANBED v1.1 Board to listen to the can bus
  for all possible data being transmitted over the bus. ie. no filter masks.
  There was an issue with the sub-D pinout. The HW comes with ODB enabled which
  allocates different pins to the sub-D that does not transmit the canH nad canL to 
  the proper wires. 
*/
#include <SPI.h>
#include "mcp_can.h"
#define SPI_CS_PIN  17 //Specific board: Canbed V1.1

MCP_CAN CAN(SPI_CS_PIN);// Set CS pin(builtin function)

void setup(){
    Serial.begin(9600);
    while(!Serial);
    while (CAN_OK != CAN.begin(CAN_500KBPS)){   // init can bus : baudrate = 500k
      //This is where we call the slow blink
    }
    Serial.println("I am the Reciever and my CAN BUS is OK!");
}

void loop(){
    unsigned char len = 0;  //Prepare a char data type to hold the length of the incoming message
    unsigned char buf[8];   //Prepare an 8 element char array to hold the incoming data
    if(CAN_MSGAVAIL == CAN.checkReceive())  // check if data coming
    {
        CAN.readMsgBuf(&len, buf);          // read data, len: data length, buf: data buffer
        unsigned long canId = CAN.getCanId(); //store the CAN id. This can take 11 or 29 bit Ids                                
        
        Serial.println("-----------------------------");  //Print the incoming data in Hexidicimal
        Serial.print("Here is the sender's id:");
        Serial.println(canId, HEX);
        Serial.println("Here is the data:");

        for(int i = 0; i<len; i++){ // print the data in the buffer
            Serial.print(buf[i]);
            Serial.print("\t");
        }      
        Serial.println();
    }  
}

/*

This is where the 

*/
// END FILE
