/*
 * Autor: Summer Lo
 * Updated date: 14/07/2022
 * Description: Design for counting the traveling time between Front sensor (Virtual) 
 * and Loading and Unloading Station Sensor (Virtual)
 * GPIO Output read status LOW = 0 
 * GPIO Output read status HIGH = 1
 * Updates: Teacher version
 */
#include "stopper.h"
#include <neotimer.h>
#include "sensor.h"
int numBlinks=0;
int count = 0;

//GPIO SetUp (Stopper)
stopper leftStopper(0);
stopper rightStopper(1);
stopper bottomConveyor(2);
stopper dispatchCargo(3);
stopper verticalCargo(4);

//GPIO SetUp (Sensor)
sensor cargoDetector(0);
sensor statusButton(1);
sensor locationSensor(2);
sensor homeSensor(3);
sensor resetSensor(4);
sensor palletDetector(5);

// Timer Setup
Neotimer t0 = Neotimer(3000);   // 3 second timer
Neotimer t1 = Neotimer(3000);   // 3 second timer
Neotimer t2 = Neotimer(5000);   // 5 second timer

int state = 0;
int deliver = 0;
unsigned long timer1;
unsigned long timer2;
unsigned long timeDiff;

void setup() {
    Serial.begin(9600);
    t0.reset();
    t2.reset();

    // Original Position
    bottomConveyor.start();
    delay(200);
    dispatchCargo.start();
    delay(200);
    verticalCargo.start();
    delay(200);

    Serial.println("Start\n");
}



void loop() {
    // put your main code here, to run repeatedly:
    
    if (state == 0)                                     // State 0
    {
        if (locationSensor.read() == 1)             // Check the location sensor
        {
            timer1 = millis();                      // Get the current time
            state = 1;                              // Set state = 1
            Serial.println("Change to State 1!");
        }  
    }
    else if (state == 1)                               // State 1
    {
        // Write your code - Begin
        if(palletDetector.read() == 1)                 // Check the pallet detector
        {
            timer2 = millis();                         // Get the current time
            Serial.println(timer2-timer1);            
            state = 0;                                 // Set state = 0
            Serial.println("Change to State 0");
        }
        // Write your code - End
    }
}
