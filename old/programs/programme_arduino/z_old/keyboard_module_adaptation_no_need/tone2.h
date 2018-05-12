// WARNING : NOT INCLUDE KeyboardModule.h IN THE SAME TIME with tone.h

    void tone(int speaker_pin, long NOTE_FREQUENCIES[], int note_duration) 
    {
      long delayValue = 1000000 / NOTE_FREQUENCIES[] / 2; // calculate the delay value between transitions
      //// 1 second's worth of microseconds, divided by the frequency, then split in half since
      //// there are two phases to each cycle
      long numCycles = NOTE_FREQUENCIES[] * note_duration / 1000; // calculate the number of cycles for proper timing
      //// multiply frequency, which is really cycles per second, by the number of seconds to
      //// get the total number of cycles to produce
      for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
        digitalWrite(speaker_pin, HIGH); // write the buzzer pin high to push out the diaphram
        delayMicroseconds(delayValue); // wait for the calculated delay value
        digitalWrite(speaker_pin, LOW); // write the buzzer pin low to pull back the diaphram
        delayMicroseconds(delayValue); // wait again or the calculated delay value
      }
     
    }

    
    void noTone(speaker_pin) {
      digitalWrite(speaker_pin, LOW);
      
    }
