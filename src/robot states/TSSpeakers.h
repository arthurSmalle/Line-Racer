// buzzer tone lib: https://github.com/hibit-dev/buzzer/tree/master
#ifndef TS_SPEAKERS_H
#define TS_SPEAKERS_H
#include "state machine/RobotState.h"
#include <Arduino.h>
#include "./pitches.h"

class TSSpeakers : public RobotState{
  public:
    // constructor (leave empty)
    // change name to name of class
    TSSpeakers(){}

  protected:
    void tokyo_drift(){
      int melody[] = {
  NOTE_AS4, REST, NOTE_AS4, REST, NOTE_AS4, REST, NOTE_AS4, REST,
  NOTE_AS4, NOTE_B4, NOTE_DS5,
  NOTE_AS4, REST, NOTE_AS4, REST,
  NOTE_AS4, NOTE_B4, NOTE_DS5,
  NOTE_AS4, REST, NOTE_AS4, REST,
  NOTE_AS4, NOTE_B4, NOTE_DS5,
  NOTE_AS4, REST, NOTE_AS4, REST,
  NOTE_AS4, NOTE_B4, NOTE_DS5,
  NOTE_F5, REST, NOTE_F5, REST,
  NOTE_GS5, NOTE_FS5, NOTE_F5,
  NOTE_AS4, REST, NOTE_AS4, REST,
  NOTE_GS5, NOTE_FS5, NOTE_F5,
  NOTE_AS4, REST, NOTE_AS4, REST,
  NOTE_AS4, NOTE_B4, NOTE_DS5,
  NOTE_AS4, REST, NOTE_AS4, REST,
  NOTE_AS4, NOTE_B4, NOTE_DS5,
  NOTE_AS4, REST, NOTE_AS4, REST,
  REST
};
int durations[] = {
  4, 4, 4, 4, 4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  1
};

 int size = sizeof(durations) / sizeof(int);

  for (int note = 0; note < size; note++) {
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 1000 / durations[note];
    tone(buzzer_pin, melody[note], duration);

    //to distinguish the notes, set a minimum time between them.
    //the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * .75;
    delay(pauseBetweenNotes);

    //stop the tone playing:
    noTone(buzzer_pin);
  }
}
    // Add variables here
    uint8_t buzzer_pin = 12;

    // Add functions here
    // functions can only be called from enter, update and go_next_state
    void example_func(){}

    // put code between {} to implement features

    // do something on start of the state (only does this once)
    void enter() override{
      pinMode(buzzer_pin, OUTPUT);
    }

    // keep looping
    void update() override{
      Serial.println("beginning music...");
      tokyo_drift();
    }
    // add logic for going to next state here
    // this is called when in in main you do:
    // ready_go_next = true;
    // this ends the update loop!
    State * go_next_state() override{}
};

#endif
