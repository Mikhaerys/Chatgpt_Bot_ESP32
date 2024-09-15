#include "music.h"
#include <Arduino.h>

int tempo = 114;
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;

int melody1[] = {
  NOTE_D5, -4, NOTE_E5, -4, NOTE_A4, 4,  //1
  NOTE_E5, -4, NOTE_FS5, -4, NOTE_A5, 16, NOTE_G5, 16, NOTE_FS5, 8,
  NOTE_D5, -4, NOTE_E5, -4, NOTE_A4, 2,
  NOTE_A4, 16, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 8, NOTE_D5, 16,
  NOTE_D5, -4, NOTE_E5, -4, NOTE_A4, 4,  //repeat from 1
  NOTE_E5, -4, NOTE_FS5, -4, NOTE_A5, 16, NOTE_G5, 16, NOTE_FS5, 8,
  NOTE_D5, -4, NOTE_E5, -4, NOTE_A4, 2,
  NOTE_A4, 16, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 8, NOTE_D5, 16,
  REST, 4, NOTE_B4, 8, NOTE_CS5, 8, NOTE_D5, 8, NOTE_D5, 8, NOTE_E5, 8, NOTE_CS5, -8,
  NOTE_B4, 16, NOTE_A4, 2, REST, 4
};

int melody2[] = {
  NOTE_A2, 5, NOTE_E3, 5, NOTE_C4, 5,
  NOTE_A5, 6, NOTE_G5, 6, NOTE_E5, 6,
  NOTE_G5, 8, NOTE_E5, 2, REST, 8, NOTE_E5, 6,
  NOTE_D5, 6, NOTE_C5, 6, NOTE_D5, 8,
  NOTE_E5, 2, REST, 8, NOTE_A5, 7, NOTE_G5, 6,
  NOTE_E5, 6, NOTE_G5, 8, NOTE_E5, 2, REST, 8,
  NOTE_E5, 6, NOTE_B4, 6, NOTE_B4, 6, NOTE_B4, 6,
  NOTE_C5, 2
};

int melody3[] = {
  NOTE_C5, 5, NOTE_D5, 6, NOTE_C5, 10, NOTE_A4, 5,
	NOTE_A4, 5, NOTE_A4, 6, NOTE_G4, 10, NOTE_A4, 6,
	NOTE_AS4, 10, NOTE_A4, 3, NOTE_AS4, 5, NOTE_G4, 6,
	NOTE_C5,10, NOTE_A4, 3, NOTE_F4, 6, NOTE_D4, 5,
	NOTE_G4, 10, NOTE_C4, 4,
};

void playMelody(int melody[]) {
  int notes = sizeof(melody) / sizeof(melody[0]) / 2;
   
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;  // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(BUZZER, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(BUZZER);
  }
}