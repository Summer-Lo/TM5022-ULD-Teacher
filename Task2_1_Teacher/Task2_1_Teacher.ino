/*
 * Autor: Summer Lo
 * Updated date: 08/07/2022
 * Description: Design for counting the traveling time between Front sensor (Virtual) 
 * and Loading and Unloading Station Sensor (Virtual)
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
Neotimer t0 = Neotimer(3000);   // 3 second timer
Neotimer t1 = Neotimer(3000);   // 3 second timer
Neotimer t2 = Neotimer(5000);   // 5 second timer

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
    bottomConveyor.start();
    delay(200);
    dispatchCargo.start();
    delay(200);
    resetCargo.start();
    delay(200);

    Serial.println("Start\n");
}



void loop() {
    // put your main code here, to run repeatedly:
    
    if (state == 0)                                         // Open all stopper and start and wait for node-red 's' response
    {
        if(t2.done())
        {   
            //Serial.println("Timer 2 End!");
            if (locationSensor.read() == 1)                            // TRANSITION CONDITION // 's' is transmitted by node-red
            {
                timer1 = millis();
                //Serial.println(timer1);
                state = 1;
                //Serial.println("Change to State 1!");
            }  
        }
    }
    if (state == 1)
    {
        if(palletDetector.read() == 1)
        {
            timer2 = millis();
            //Serial.println(timer2);
            Serial.println(timer2-timer1);
            state = 0;
            //Serial.println("Change to State 0");
            t2.start();
        }
    }
}
