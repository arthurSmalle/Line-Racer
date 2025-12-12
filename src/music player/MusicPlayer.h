#ifndef MUSIC_PLAYER_h
#define MUSIC_PLAYER_h
#include <Arduino.h>
class MusicPlayer{
  public:
    void set_song(int melody[], const int durations[], const int size, const float pause_modifier = 0.70){
      this->size = size;
      this->melody = melody;
      this->durations = durations;
      this->music_position = 0;
      this->pause_modifier = pause_modifier;
      this->has_song = true;
    }

    void set_speed_mod(const float speedmod);
    void set_pin(const uint8_t pin){this->buzzer_pin = pin;}
    void set_pause_modifier(const float pause_modifier){this->pause_modifier = pause_modifier;}

    int get_size(){return this->size;};
    int get_current_pos(){return this->music_position;}
    int get_current_note(){return this->melody[music_position];}
   
    void play(){if(has_song){playing = true;}}
    void pause(){playing = true;}
    void reset(){music_position = 0;}
    void stop(){
      music_position = 0;
      playing = false;
    }
    void set_loop(const bool loop){this->loop = loop;}

    void update(){
      if (music_position < size && playing){
	unsigned long current_time = millis();
        //to calculate the note duration, take one second divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int duration = 1000 / durations[music_position];
        //to distinguish the notes, set a minimum time between them.
        //the note's duration + 30% seems to work well:
        int pauseBetweenNotes = duration * this->pause_modifier;
	
	if ((current_time - last_beep_time) > pauseBetweenNotes){
	  last_beep_time = current_time;
          //stop the tone playing:
          noTone(buzzer_pin);
	  tone(buzzer_pin, melody[music_position], duration);
	  music_position++;
	}
      } else if (loop) {
	reset();
      } else {
	stop();
      }
    }

    MusicPlayer(const uint8_t pin){
      this->buzzer_pin = pin;
    }

    MusicPlayer(const uint8_t pin,int melody[],int durations[], const int size): MusicPlayer(pin){
      set_song(melody, durations, size);
    }

  private:
    int * melody;
    const int * durations;
    int music_position = 0;
    int size;
    bool has_song;

    uint8_t buzzer_pin;
    bool playing = false;
    bool loop = true;
    float pause_modifier = 1.30;

    unsigned long last_beep_time = 0;

};
#endif
