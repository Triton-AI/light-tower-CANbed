// Include the required libraries
#include <Arduino.h>
#include <SPI.h>
#include "mcp_can.h"

//Can Bus CS pin using LONGAN library
const int SPI_CS_PIN = 17; 

// Define the LED pin
const int greenLedPin  = 11;
const int redLedPin    = 10;
const int yellowLedPin = 9;
const int buzzerPin    = 8;

const int rotatingYellowPin    = A0;
const int RotatingYellowSwitch = A1;
// Define the blink rate in milliseconds
unsigned long slowBlinkRate = 1000; // Default slow blink rate is 1 second
unsigned long fastBlinkRate = 50; // Default slow blink rate is 1 second
unsigned long buzzerTime = 3000; // Default bbuzzer duration is 3 s
unsigned long canId = 0;
// Variables to track timing
unsigned long greenPreviousTime = 0;
bool greenLedState = false;
unsigned long redPreviousTime = 0;
bool redLedState = false;
unsigned long yellowPreviousTime = 0;
bool yellowLedState = false;
unsigned long buzzerPreviousTime = 0;
bool buzzerState = false;

unsigned long greenCurrentTime = 0;


MCP_CAN CAN(SPI_CS_PIN);   //Set CS Pin using SEEED Library

void setup() {
  // Initialize the LED pin as an output
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(115200);
  while (!Serial);
  while (CAN_OK != CAN.begin(CAN_500KBPS)) {
    Serial.println("CAN BUS FAIL!");
    delay(100);
  }
  Serial.println("CAN BUS OK!");
}

void loop() {
  unsigned char len = 0;    //Variables which acquire Can-Bus message data
  unsigned char buf[8];
  unsigned char pastBuf[8];
  if (CAN_MSGAVAIL == CAN.checkReceive()) {  //Check if a CAN signal is available

    //CAN.readMsgBuf(&len, buf);    // read data.  len = data length, buf = data buffer
    //Serial.println("New message from CAN was read");
    //canId = CAN.getCanId();

    //displayCANData(buf, len, canId);
    
    //towerControl(buf[0]);
    /*if(canId == XX) {
      //Type cast to int?
      towerControl(buf[0]);//Pass the Can message as an integer to towerControl to decide what function to perform
    }*/

  }
  towerControl(0);


}

void towerControl(int CAN_message) {
  switch(CAN_message) {
    case 0:
      slowGreenBlink();
      break;
    case 1:
      slowRedBlink();
      break;
    case 2:
      slowYellowBlink();
      break;
    case 3:
      fastGreenBlink();
      break;
    case 4:
      fastRedBlink();
      break;
    case 5:
      fastYellowBlink();
      break;
    case 6:
      slowRedBlink();
      fastYellowBlink();
      runBuzzerOnce();
      break;
    case 7:
      //Insert light function here
      break;
    default:
      // Handle invalid CAN_message here if needed
      break;
  }
}

void shutDown(int pin_1, int pin_2, int pin_3) {
  turnOff(pin_1);
  turnOff(pin_2);
  turnOff(pin_3);
}

void slowRedBlink() {
  // Get the current time
  unsigned long redCurrentTime = millis();
  // Check if the desired blink rate has elapsed
  if (redCurrentTime - redPreviousTime >= slowBlinkRate) {
    // Update the previous time
    redPreviousTime = redCurrentTime;
    // Toggle the LED state
    redLedState = !redLedState;
    // Set the LED state
    if (redLedState) {
      turnOn(redLedPin);
    } 
    else {
      turnOff(redLedPin);
    }
  }
}

void fastRedBlink() {
  unsigned long redCurrentTime = millis();
  if (redCurrentTime - redPreviousTime >= fastBlinkRate) {
    redPreviousTime = redCurrentTime;
    redLedState = !redLedState;
    if (redLedState) {
      turnOn(redLedPin);
    } 
    else {
      turnOff(redLedPin);
    }
  }
}

void slowGreenBlink() {
  unsigned long greenCurrentTime = millis();
  if (greenCurrentTime - greenPreviousTime >= slowBlinkRate) {
    greenPreviousTime = greenCurrentTime;
    greenLedState = !greenLedState;
    if (greenLedState) {
      turnOn(greenLedPin);
    } 
    else {
      turnOff(greenLedPin);
    }
  }
}

void fastGreenBlink() {


  unsigned long greenCurrentTime = millis();
  if (greenCurrentTime - greenPreviousTime >= fastBlinkRate) {
  greenPreviousTime = greenCurrentTime;
  greenLedState = !greenLedState;
  if (greenLedState) {
    turnOn(greenLedPin);
    Serial.println("turned on");
  } 
    else {
    turnOff(greenLedPin);
  }
  
  }
  
}

void slowYellowBlink() {
  unsigned long yellowCurrentTime = millis();
  if (yellowCurrentTime - yellowPreviousTime >= slowBlinkRate) {
    yellowPreviousTime = yellowCurrentTime;
    yellowLedState = !yellowLedState;
    if (yellowLedState) {
      turnOn(yellowLedPin);
    } 
    else {
      turnOff(yellowLedPin);
    }
  }
}

void fastYellowBlink() {
  unsigned long yellowCurrentTime = millis();
  if (yellowCurrentTime - yellowPreviousTime >= fastBlinkRate) {
    yellowPreviousTime = yellowCurrentTime;
    yellowLedState = !yellowLedState;
    if (yellowLedState) {
      turnOn(yellowLedPin);
    } 
    else {
      turnOff(yellowLedPin);
    }
  }
}

void runBuzzerOnce(){//Lil Tricky to run once
 
  unsigned long buzzerCurrentTime = millis();
  if (buzzerCurrentTime - buzzerPreviousTime >= 3000) {
    buzzerPreviousTime = buzzerCurrentTime;
    buzzerState = !buzzerState;
    if (buzzerState) {
      turnOn(buzzerPin);
    } 
    else {
      turnOff(buzzerPin);
    }
  }
}

void turnOn(int pin) {
  //analogWrite(pin, 255);
  digitalWrite(pin, HIGH);
}

void turnOff(int pin) {
  //analogWrite(pin, 0);
  digitalWrite(pin, LOW);
}


void displayCANData(unsigned char buffer[], unsigned char length, unsigned long id) {
  Serial.println("-----------------------------");  //Print the incoming data in Hexidicimal
  Serial.print("Here is the sender's id:");
  Serial.println(id, HEX);
  Serial.println("Here is the data:");

  for(int i = 0; i<length; i++){ // print the data in the buffer
    Serial.print(buffer[i]);
    Serial.print("\t");
  }      
  Serial.println();
}

