/* Arduino code for a polystyrene foam electronic MIDI drum kit.
 *  This uses the piezoelectric effect to register each pad strike,
 *  as well as the velocity of each strike. 
 */

#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

#define LED 13   

// these constants won't change:
int padLimit = 1010;
int howHard = 1024;
int threshold[] = {38, 42, 40, 50};
int knockSensor;
int notes[] = {54, 60, 70, 80};
int hitTime[4];

// these variables will change:
int sensorReading = 0;      // variable to store the value read from the sensor pin
int ledState = LOW;         // variable used to store the last LED status, to toggle the light

void setup() {
 pinMode(LED, OUTPUT);
    MIDI.begin(4);          // Launch MIDI and listen to channel 4
}

void loop() {
  for(knockSensor = 2; knockSensor < 6; knockSensor++) {
  // read the sensor and store it in the variable sensorReading:
  if(analogRead(knockSensor) > threshold[knockSensor-2]) {
    if (millis() - hitTime[knockSensor-2] > 50) {
    digitalWrite(LED,HIGH);
    /*
      if (analogRead(knockSensor) < howHard) {
        howHard = analogRead(knockSensor);
        howHard = padLimit - analogRead(knockSensor);
         howHard *= 20;
       constrain(howHard, 0, 127);
      } */
        MIDI.sendNoteOn(notes[knockSensor-2],127,1);  // Send a Note (pitch 42, velo 127 on channel 1)
       delay(10);
       MIDI.sendNoteOff(notes[knockSensor-2],127,1);
       hitTime[knockSensor-2] = millis();
    }
  }
  digitalWrite(LED,LOW);
  howHard = 1024;
  //delay(10);  // delay to avoid overloading the serial port buffer
}
delay(15);
}

