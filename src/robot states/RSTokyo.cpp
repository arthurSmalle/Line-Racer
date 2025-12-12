#include "RSTokyo.h"
#include "state machine/StatesEnum.h"
#include "../music player/music.h"
void RSTokyo::enter(){
  motor_cl_l.set_clock_wise(false);
  motor_cl_r.set_clock_wise(false);
  motor_cl_l.enable();
  motor_cl_r.enable();
  motor_cl_l.set_set_point(base_speed);
  motor_cl_r.set_set_point(base_speed);
  // MUSIC STUFF
  music_player.set_song(tokyo_melody, tokyo_durations, tokyo_size);
  music_player.set_loop(true);
  music_player.reset();
  music_player.play();
  pinMode(MUSIC_PIN, OUTPUT);
}

void RSTokyo::update(){
  // UPDATE MOTORS AND CONTROL
  RobotState::update();
  music_player.update();
  // DEBUG PRINT
#ifdef DEBUG
  Serial.println("$$P-auto,00,00,00,00,40");
  // note: 40 is code for this state (usefull to see in plotting software)
#endif
}

StatesEnum RSTokyo::go_next_state(){
  music_player.stop();
}
