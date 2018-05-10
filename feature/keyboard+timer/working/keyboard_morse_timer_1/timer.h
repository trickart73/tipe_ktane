#ifndef Timer_h
#define Timer_h

#include "SevSeg.h"


  // VARIABLES RELATIVES AU TEMPS
long time_elapsed_since_launched_sec = 0; //Time elapsed since the timer was launched
long time_max_bomb; 
boolean time_out;


  //BUZZER
const int buzzer_timer_pin = 52;
const int note_duration = 165;


SevSeg sevseg; //7 segment of timer


class Timer
{

  public:

   
   enum State
    {
      PAUSE, TIMER_RUN, TIMER_SOUND, TIMER_STOP
    };


  Timer(){


    byte numDigits = 4;
    byte digitPins[] = {2, 3, 4, 5};
    byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
    sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
    sevseg.setBrightness(90);

    reset();

  }


  void reset()
    {
      state_ = PAUSE;

      first_time_second_refreshed_ = 0;
      last_time_note_playing_updated_ = 0;
      digitalWrite(buzzer_timer_pin,LOW);
      current_cycle_number_ = 0;

    }

   void start()
   {
    if(state_ == PAUSE)
        {
                       
           time_max_bomb = 300; //s                                             
           Serial.print("Launched for : ");
           Serial.print(time_max_bomb);
           Serial.println(" secondes");
           time_timer_launched_ = millis();
           time_out = false;

           state_ = TIMER_RUN;
           
           return;
         
        }
   }


   void update_timer()
    {

        if(state_ == PAUSE)
        {
           return;
        }
         

        else if(state_ == TIMER_RUN)
        {
           
            time_elapsed_since_launched_sec = (millis() - time_timer_launched_) / 1000; //en s
            //Serial.println(time_elapsed_since_launched_sec);

            /*if(time_elapsed_since_launched_sec != last_time_elapsed_)
            {
              Serial.println("A beep is playing");
              state_ = TIMER_SOUND;
              return;
            }*/
            
            if(time_elapsed_since_launched_sec >= time_max_bomb)
            {
              //Serial.println("Bomb exploded (in timer module)");
              time_out = true;
              state_ = PAUSE;
              return;
            }
            
            sevseg.setNumber(resting_time(time_elapsed_since_launched_sec), 2);
            sevseg.refreshDisplay();

            last_time_elapsed_ = time_elapsed_since_launched_sec;                
          
        }


        /*if(state_ == TIMER_SOUND)
        {
            int frequency = 330;
            
            long delayValue = 1000000 / frequency / 2; //delay en microsecondes
            //Serial.println("Delay Value is");
            //Serial.println(delayValue);
            long numCycles = frequency * 165 / 1000; //165 = note_duration (defined in KeyboardModule.h)
    
            unsigned long current_time = micros();
            //Serial.println("Current time is");
            //Serial.println(current_time);
            
            if(current_time - last_time_note_playing_updated_ >= delayValue)
            {       
              int state_targetpin = digitalRead(buzzer_timer_pin);
    
              if (state_targetpin == HIGH)
              {
                digitalWrite(buzzer_timer_pin,LOW);
                current_cycle_number_ ++;
                //Serial.println("Current cycle is");
                //Serial.println(current_cycle_number_);
              }
    
              else
              {
                digitalWrite(buzzer_timer_pin,HIGH);  
              }
              
            last_time_note_playing_updated_ = micros();
              
            }
    
            if(current_cycle_number_ == numCycles)
            {
              Serial.println("Bien sorti dans le timer sound");
              state_ = TIMER_RUN;
              current_cycle_number_ = 0;
              last_time_note_playing_updated_ = 0;
              digitalWrite(buzzer_timer_pin,LOW);   //this is not necessary
            }
            
          }*/
           
    }
    

    int resting_time(int currentTime) {
      int resting_time_in_min_and_sec=0;
      int resting_min = (time_max_bomb - currentTime) / 60;
      int resting_sec = (time_max_bomb - currentTime) % 60;
      return resting_time_in_min_and_sec = resting_min * 100 + resting_sec;
    }

  
    //Useful variables for NOTE_PLAYING state
    unsigned long last_time_note_playing_updated_;     
    int current_cycle_number_;
    
    int first_time_second_refreshed_;
    long last_time_elapsed_;

    long time_timer_launched_; //time when we launch timer

    State state_;
    
};

#endif