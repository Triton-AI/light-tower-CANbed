# light-tower-CANbed
Source code and resources for light lower control

# Autonomous evGoKart Light Tower Software Requirements V0.01

### 26Apr23


## Communication

- Configure CAN ID to 04
- Configure the CANbus communication protocol to be compatible with what we have been using already. Figure out the settings that you need to place in the Arduino?
- Test the communication with the Arduino and the RTC, send messages between them. Talk to the ECE 191 team working on the RTC

## Relay board
- Connect the power of the board to 5V
- Connect the 4 inputs from the relay to 4 pins of the Arduino
- Show that you can control each I/O (easy 1/0) at the I/O. You should hear the clicks on the relays on and off
- Connect the light tower to the relays R, Y, G, and Buzzer on the NO (normally open). Ground wire (black?) to the 12V -. 
- Connect 12V to the C (common) of each relay, they are basically chain connected together to 12V +. 
- Show that they each light and buzzer works

- Investigate to see if this Arduino has a watch-dog. If so, learn how to use it. Enable it with a time variable called watch-dog-time and set it in ms (milliseconds) on the header of the code. Not hard coding in the middle of the code. Use a variable that we can easily change on the top of the code.  Default value is 50 ms. That is, the Arduino will reboot if the watch-dog is not reset every 50 ms

- Learn how to not use delays to wait for some time. Delays are a waste of MCU computation power. There are lots of code examples to do a class/ function that replicate the delay functionality

- Heart beat. Learn how to use timers. Set a variable called heart-beat-time. Set it in ms (milliseconds) on the header of the code. 
Listen to the Can communication heart-beat. If you don't hear the heart-beat in the time set at heart-beat-time, turn on the RED light flashing by red-light-flashing-time. Set variable in ms at the header with 250 ms. Heartbeat message being sent over CAN: “rtc-heartbeat”

- Light Control Protocol. Develop a protocol that has the following format

## C-T-R  (Color Time Repeat)
ex: red-250-1.  That means red color flash once at 250 ms
0 means light off
1 means light on constant
ex:
green-1-x.   That is green light constant on
green-0-x. That is green light off
That means you need to check for 1 or 0 before passing the ms time to the code
buzzer-250-2. That buzzer is on every 250 ms twice then off…

Note: it would be good to support not just red, green and blue colors but a mix of RGB colors (orange or purple for example).

Keep the same state until you receive the next command. That means you need to remember the state for each light and buzzer independently and your code needs to deal with multiple lights and or buzzer on at the same time until you get a command to turn them off.
If you don't hear the heart-beat then turn off all the lights and flash red with the heart-beat-time. We will know that we lost the heart beat
 Let the high level computer decide what to do with the lights by sending commands to the Arudino

Develop and publish a set of ROS2 messages from the high level node to the VASS (Vehicle Alert Signaling System) …  Write a test publisher ROS2 Node to run a script (or a set of scripts) to go through and operate the VASS. 

##  Yellow Light Modes (Yellow wire acts as a switch when it receives 24V)

1. Slow Blink
2. Triple burst high low
3. Triple burst low hi
4. CCW slow
5. CW slow
6. CCW fast
7. CW slow  

## Light Tower Modes

1. Steady green - Sutonomous mode 
2. Greenflash/rotate - Receiving commands from agx for throttle and in auto mode
3. Buzzer - Before moving
4. Yellow - Manual mode
5. Yellow flashing/rotate - Manual mode receiving throttle commands from remote
6. Flash red slow - No commmunication from rtc to arduino
7. Fast red flash - No comms from agx to rtc(may be a tricky one)