//******************************************************************
// Nara Rzayeva
// February 12th, 2020
// 
// Techno Harp project's purpose is to allow users play
// any instrument sound with the use of water.
// There are 2 modes for water enabling sound:
//  1. Using hairless-midiserial
//  2. Using Piezo speakers (buzzers)
// Method 1 will require a call to playTone() function whereas
// Method 2 will require a call to enableBuzzer() function.
//
// There are also helpful debugging logs which can be enabled by
// setting DEBUG variable into 1.
//******************************************************************

#include <MIDI.h>

// cup sensors
int cup_one = A0;
int cup_two = A4;
int cup_three = A10;
int cup_four = A12;
int cup_five = A13;

// buzzers
int buzz_one = 11;
int buzz_two = 10;
int buzz_three = 38;
int buzz_four = 48;
int buzz_five = 51;

int DEBUG = 0; // variable for setting debug mode on/off
MIDI_CREATE_DEFAULT_INSTANCE();

void setup(){
  MIDI.begin(MIDI_CHANNEL_OMNI); // midi communication
  Serial.begin(9600); // serial communication for debugging
  
  // initialize water sensors
  pinMode(cup_one, INPUT);
  pinMode(cup_two, INPUT);
  pinMode(cup_three, INPUT);
  pinMode(cup_four, INPUT);
  pinMode(cup_five, INPUT);
  
  // initialize buzzers
  pinMode(buzz_one, OUTPUT);
  pinMode(buzz_two, OUTPUT);
  pinMode(buzz_three, OUTPUT);
  pinMode(buzz_four, OUTPUT);
  pinMode(buzz_five, OUTPUT);
}

/**
 * Function for playing tones through buzzers
 */
void enableBuzzer(int cup_number, int buzz_number, int tone_frequency) {
  if (cup_number > 500) {
     tone(buzz_number, tone_frequency);
     delay(500);
  } else {
     noTone(buzz_number);
     delay(500);
  }
}

/**
 * Function for playing sounds through MIDI interface
 */
void playTone(int cup_number, int tone_frequency) {
  if (cup_number > 500) {
     MIDI.sendNoteOn(tone_frequency, 127, 1);
     delay(500);
  } else {
     MIDI.sendNoteOff(tone_frequency, 127, 1);
     delay(500);
  }
}
 

void loop(){
  // enable in order to get debugging logs
  if (DEBUG) {
    Serial.println("=========================");
    int sensor1=analogRead(cup_one);
    Serial.print("cup_one: ");
    Serial.println(sensor1);
    int sensor2=analogRead(cup_two);
    Serial.print("cup_two: ");
    Serial.println(sensor2);
    int sensor3=analogRead(cup_three);
    Serial.print("cup_three: ");
    Serial.println(sensor3);
    int sensor4=analogRead(cup_four);
    Serial.print("cup_four: ");
    Serial.println(sensor4);
    int sensor5=analogRead(cup_five);
    Serial.print("cup_five: ");
    Serial.println(sensor5);
    Serial.println("=========================");
  }

  //// Reading water sensor values and playing different tones associated with the sensor ////
  int sensor_one = analogRead(cup_one);
  playTone(sensor_one, 50); // Plays a tone 50 in Hz

  int sensor_two = analogRead(cup_two);
  playTone(sensor_two, 41); // Plays a tone 41 in Hz

  int sensor_three = analogRead(cup_three);
  playTone(sensor_three, 40); // Plays a tone 40 in Hz

  int sensor_four = analogRead(cup_four);
  playTone(sensor_four, 39); // Plays a tone 39 in Hz

  int sensor_five = analogRead(cup_five);
  playTone(sensor_five, 38); // Plays a tone 38 in Hz

  // Uncomment the following lines in order to use the buzzer
  // int sensor_one = analogRead(cup_one);
  // enableBuzzer(sensor_one, buzz_one, 261); // Sounds the buzzer at the frequency relative to the note C in Hz
}
