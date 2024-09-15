#ifndef MUSIC_H
#define MUSIC_H

//Definition of notes to play melodies on a buzzer
#define NOTE_A2 110
#define NOTE_E3 165
#define NOTE_C4 262
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_D4 294
#define NOTE_B4 494
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_E5 659
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_A5 880
#define REST 0

#define BUZZER 15

extern int melody1[];
extern int melody2[];
extern int melody3[];

void playMelody(int melody[]);

#endif