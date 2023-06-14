#include "mbed.h"
CAN can(PE_0, PE_1, 500000); // CAN interface pins and baud rate

int main() {
    CANMessage msg;
    msg.id = 0x12345678;       // Extended message identifier
    msg.len = 3;               // Data length (up to 8 bytes)
    msg.format = CANExtended;  // Set frame format to extended
    msg.data[0] = 0xAB;        // Data byte 0
    msg.data[1] = 0xCD;        // Data byte 1
    msg.data[2] = 0xEF;        // Data byte 2

    while (1) {
        can.write(msg);        // Send the CAN message
        wait(1);               // Wait for 1 second
    }
}