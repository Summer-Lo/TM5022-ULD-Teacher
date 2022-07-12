/*
 * Autor: Summer Lo
 * Updated date: 08/07/2022
 * Description: Design a step squence program for attaching the action in simultation and PLC via Raspberry Pi
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
Neotimer t0 = Neotimer(1600);   // 1.6 second timer
Neotimer t1 = Neotimer(3000);   // 3 second timer
Neotimer t2 = Neotimer(11000);   // 5.3 second timer

int state = 0;
int deliver = 0;
char message;
char store;
unsigned long timer1;
unsigned long timer2;
unsigned long timeDiff;

void setup() {
    Serial.begin(9600);
    t0.reset();
    t2.reset();
    //t0.start();
    t2.start();

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
    
    if (state == 0)                                                // Check cargo ready or not
    {
        if (homeSensor.read() == 1)                            // TRANSITION CONDITION // Dispatch sensor detected cargo
        {
            state = 1;
            Serial.println("The Cargo is ready to dispatch");
            Serial.println("Change to State 1!");
        }  
    }
    
    else if (state == 1)                                           // Check Front Sensor signal
    {
        //Serial.println("Timer 2 End!");
        if (locationSensor.read() == 1)                               // TRANSITION CONDITION // Front Sensor detected cargo
        {
            state = 2;
            t2.start();
            Serial.println("Front Sensor read sucessfully!");
            Serial.println("Change to State 2!");
        }  
    }
    
    else if (state == 2)                                           // Dispatch cargo when time out
    {
        if (t2.done())                                             // TRANSITION CONDITION // Timer 2 run out
        {
            dispatchCargo.start();
            Serial.println("Cargo is dispatched!");
            state = 3;
            Serial.println("Change to State 3!");
        }
    }

    else if (state == 3)                                           // End process and return
    {
        if(cargoDetector.read() == 1)                              // TRANSITION CONDITION // Loading and unloading sensor detected cargo
        {
            state = 0;
            t0.start();
            Serial.println("Change to State 0!");
        }
    }
}
