/*
 * Autor: Summer Lo
 * Updated date: 14/07/2022
 * Description: Design a step squence program for complete the mission
 * 
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
stopper ULDsetup(5);

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
Neotimer t2 = Neotimer(13500);   // 5.3 second timer

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
    bottomConveyor.activate();
    delay(200);
    //dispatchCargo.activate();
    ULDsetup.activate();
    delay(200);
    verticalCargo.activate();
    delay(200);

    Serial.println("Start\n");
}



void loop() {
    // put your main code here, to run repeatedly:
    
    if (state == 0)                                 // State 0
    {
        if (locationSensor.read() == 1)             // Check the location sensor
        {
            Serial.println("Location sensor is activated!");
            state = 1;                              // Set state = 1
            t0.start();                             // Start the timer t0
            Serial.println("Change to State 1!");  
        }  
    }
    
    else if (state == 1)                            // State 1
    {
        if (t0.done())                              // Check the t0 > 2s
        {
            // Write your code - Begin
            t0.reset();
            Serial.println("The t0 runs out!");
            Serial.println("Cargo is dispatched!");
            dispatchCargo.start();                  // Disptach the cargo
            state = 2;                              // Set state = 2
            Serial.println("Change to State 2!");
            // Write your code - End
        }  
    }

    else if (state == 2)                            // State 2
    {
        // Write your code - Begin 
        if (Serial.read() == 'e')                   // Check the serial input == "e" character
        {
            Serial.println("Done!");
            state = 0;                              // Set state = 0
            Serial.println("Change to State 0!");
        }
        // Write your code - End        
    }
}
