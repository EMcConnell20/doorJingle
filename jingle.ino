#include <ESP8266WiFi.h>

#define AUDIO_PIN D6

// Notes & Pitch //

enum Pitch {
  C,
  D,
  E,
  F,
  G,
  A,
  B,
};

struct Note {
  Pitch pitch;
  bool sharp;
  byte octave;
  byte degree; // 0 = Whole Note | 1 = Half Note | 2 = Quarter Note
};

unsigned int get_frequency(const Note* note) {
  double hertz = 0.0;

  switch (note->pitch) {
    case C: hertz = note->sharp ? 17.32 : 16.35; break;
    case D: hertz = note->sharp ? 19.45 : 17.32; break;
    case E: hertz = note->sharp ? 21.83 : 20.6; break;
    case F: hertz = note->sharp ? 23.12 : 21.83; break;
    case G: hertz = note->sharp ? 25.96 : 24.5; break;
    case A: hertz = note->sharp ? 29.14 : 27.5; break;
    case B: hertz = note->sharp ? 32.7 : 30.87; break;
  }

  hertz *= pow(2.0, static_cast<double>(note->octave));
  return static_cast<unsigned int>(hertz);
}

const Note QUARTER_C3 = { C, false, 3, 2 };
const Note QUARTER_D3 = { D, false, 3, 2 };
const Note QUARTER_E3 = { E, false, 3, 2 };
const Note QUARTER_F3 = { F, false, 3, 2 };
const Note QUARTER_G3 = { G, false, 3, 2 };
const Note QUARTER_A4 = { A, false, 4, 2 };
const Note QUARTER_B4 = { B, false, 4, 2 };

// Tempo & Timing //

double tempo = 60.0;

unsigned int note_duration(byte degree) {
  return static_cast<unsigned int>((60.0 / tempo * 1000.0) / pow(2.0, static_cast<double>(degree)));
}

void play_note(const Note* note) {
  tone(AUDIO_PIN, get_frequency(note), note_duration(note->degree));
  delay(note_duration(note->degree));
}

// Setup //

void setup() {
  Serial.begin(115200);
}

// Loop //

void loop() {
  play_note(&QUARTER_C3);
  play_note(&QUARTER_D3);
  play_note(&QUARTER_E3);
  play_note(&QUARTER_F3);
  play_note(&QUARTER_G3);
  play_note(&QUARTER_A4);
  play_note(&QUARTER_B4);
}
