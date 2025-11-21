// buzzer tone lib: https://github.com/hibit-dev/buzzer/tree/master
#ifndef TS_SPEAKERS_H
#define TS_SPEAKERS_H
#include "state machine/RobotState.h"
#include <Arduino.h>
#include "../music player/MusicPlayer.h"
#include "../music player/music.h"
#include "state machine/StatesEnum.h"

class TSSpeakers : public RobotState{
  public:
    // constructor (leave empty)
    // change name to name of class
    TSSpeakers(){}

  protected:
    // Add variables here
    uint8_t buzzer_pin = MUSIC_PIN;

    // Add functions here
    // functions can only be called from enter, update and go_next_state
    void example_func(){}

    // put code between {} to implement features

    // do something on start of the state (only does this once)
    void enter() override{
      pinMode(buzzer_pin, OUTPUT);
      music_player.set_loop(true);
      music_player.set_song(tokyo_melody, tokyo_durations, tokyo_size, .75);
      music_player.play();
    }

   int music_pos = 0;
    // keep looping
    void update() override{
      music_player.update();
	//      if (music_pos != music_player.get_current_pos()){
	// music_pos = music_player.get_current_pos();
	// Serial.println(music_pos);
	// Serial.println(music_player.get_current_note());
	//      }
    }
    StatesEnum go_next_state() override{}
};

#endif
