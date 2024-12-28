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
}

struct Note {
  Pitch pitch;
  bool sharp;
  byte octave;
  byte degree; // 0 = Whole Note | 1 = Half Note | 2 = Quarter Note
};

unsigned int get_frequency(struct *Note note) {
  double hertz = 0.0;

  switch(note.pitch) {
    case (Pitch::C):
      output = note.sharp ? 17.32 : 16.35;
      break;
    case (Pitch::D):
      output = note.sharp ? 19.45 : 17.32;
      break;
    case (Pitch::E):
      output = note.sharp ? 21.83 : 20.6;
      break;
    case (Pitch::F):
      output = note.sharp ? 23.12 : 21.83;
      break;
    case (Pitch::G):
      output = note.sharp ? 25.96 : 24.5;
      break;
    case (Pitch::A):
      output = note.sharp ? 29.14 : 27.5;
      break;
    case (Pitch::B):
      output = note.sharp ? 32.7 : 30.87;
      break;
  }

  hertz *= pow(2.0, note.octive.toDouble());
  return trunc(hertz);
}

const struct Note QUARTER_C3 = { Pitch::C, false, 3, 2 };
const struct Note QUARTER_D3 = { Pitch::D, false, 3, 2 };
const struct Note QUARTER_E3 = { Pitch::E, false, 3, 2 };
const struct Note QUARTER_F3 = { Pitch::F, false, 3, 2 };
const struct Note QUARTER_G3 = { Pitch::G, false, 3, 2 };
const struct Note QUARTER_A4 = { Pitch::A, false, 4, 2 };
const struct Note QUARTER_B4 = { Pitch::B, false, 4, 2 };

// Tempo & Timing //

double tempo = 60.0;

void play_note(struct *Note note) {
  tone(AUDIO_PIN, get_frequency(note), note_durration(note.degree));
}

unsigned int note_durration(byte degree) {
  // Mins / BPM * 1000ms
  // Auto Conversion Probably?
  return unsigned int (60.0 / tempo * 1000.0 / pow(2.0, degree.toDouble()));
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
