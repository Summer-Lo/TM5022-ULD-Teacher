/*
 * Autor: Summer Lo
 * Updated date: 13/07/2022
 * Description: Design a step squence program for complete the mission
 * 
 * GPIO Output read status LOW = 0 
 * GPIO Output read status HIGH = 1
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
stopper resetCargo(4);

//GPIO SetUp (Sensor)
sensor cargoDetector(0);
sensor statusButton(1);
sensor locationSensor(2);
sensor homeSensor(3);
sensor resetSensor(4);
sensor palletDetector(5);

// Timer Setup
Neotimer t0 = Neotimer(2000);   // 2 second timer
Neotimer t1 = Neotimer(3000);   // 3 second timer
Neotimer t2 = Neotimer(5000);   // 5 second timer

int state = 0;
unsigned long timer1;
unsigned long timer2;
unsigned long timeDiff;

void setup() {
    Serial.begin(9600);
    t0.reset();
    t2.reset();

    // Original Position
    bottomConveyor.activate();
    delay(200);
    dispatchCargo.activate();
    delay(200);
    resetCargo.activate();
    delay(200);

    Serial.println("Start\n");
}



void loop() {
    // put your main code here, to run repeatedly:
    
    if (state == 0)                               // Practicing GPIO connection between Arduino and Raspberry Pi
    {
        //Serial.println("Timer 2 End!");
        if (locationSensor.read() == 1)              // TRANSITION CONDITION 
        {
            state = 1;
            Serial.println("Front Sensor read sucessfully!");
            t0.start();
            Serial.println("Change to State 1!");
        }  
    }
    
    else if (state == 1)                          // Practicing Timing counter process
    {
        //Serial.println("Timer 2 End!");
        if (t0.done())                            // TRANSITION CONDITION
        {
            Serial.println("Timer 0 run out!");
            dispatchCargo.start();
            Serial.println("Cargo is dispatched!");
            state = 2;
            Serial.println("Change to State 2!");
        }  
    }
    
    else if (state == 2)                          // Practicing Serial Read from user input
    {
        if (Serial.read() == 'e')                 // TRANSITION CONDITION
        {
            Serial.println("Done!");
            state = 0;
            Serial.println("Change to State 0!");
        }
    }
}
