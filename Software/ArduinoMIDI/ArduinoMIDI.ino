/*
 * bigKNOB midi github.com/leafcutterlabs/bigKNOB/
 */

#include <MIDIUSB.h>
#include <pitchToNote.h>
#include <frequencyToNote.h>
#include <FastLED.h>
#include <Bounce2.h>

#define BUTTON_PIN_0 4 //D4 next to encoder
#define BUTTON_PIN_1 12 //D6
#define BUTTON_PIN_2 A1 //F6
#define BUTTON_PIN_3 A0 //F7 farthest right
#define BUTTON_PIN_R 11 //B7 Encoder button

int prevButton2, prevButton3;

byte vollev = 64;

//Underglow Setup
#define LED_PIN     13 //C7
#define NUM_LEDS    5
#define BRIGHTNESS  32
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#include <SimpleRotary.h>

#define UPDATES_PER_SECOND 100

//midi stuff
#define MIDI_CHANNEL 0   //Default MIDI channel
int LOWEST_NOTE = 60;   //lowest note starting with encoder knob, only used for sending note info

SimpleRotary rotary(3,0,11); //D2 D0 B7

// Instantiate a Bounce object
Bounce debouncer0 = Bounce(); 
Bounce debouncer1 = Bounce(); 
Bounce debouncer2 = Bounce(); 
Bounce debouncer3 = Bounce(); 
Bounce debouncerR = Bounce(); 

void setup() {
  Serial.begin(9600);
  Serial.println("Connected:");
  delay(1500); // power-up safety delay for LEDs
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);
  // Setup the button with an internal pull-up :
  pinMode(BUTTON_PIN_R,INPUT_PULLUP);
  debouncerR.attach(BUTTON_PIN_R);
  debouncerR.interval(5); // interval in ms
  pinMode(BUTTON_PIN_0,INPUT_PULLUP);
  debouncer0.attach(BUTTON_PIN_0);
  debouncer0.interval(5); // interval in ms
  pinMode(BUTTON_PIN_1,INPUT_PULLUP);
  debouncer1.attach(BUTTON_PIN_1);
  debouncer1.interval(5); // interval in ms
  
}

void loop() {
  if (abs(analogRead(BUTTON_PIN_2)-prevButton2)>200){ //change on button 2
    delay(5); //debounce
    if(abs(analogRead(BUTTON_PIN_2)-prevButton2)>200) prevButton2=analogRead(BUTTON_PIN_2);
    if(prevButton2<100){//button pressed down
      controlChange(MIDI_CHANNEL,3,127);
      //noteOn(MIDI_CHANNEL,LOWEST_NOTE+3,127);
      MidiUSB.flush();
      Serial.println("2");
    }
    if(prevButton2>800){ //button up
      controlChange(MIDI_CHANNEL,3,0);
      MidiUSB.flush();
    }
  }
  if (abs(analogRead(BUTTON_PIN_3)-prevButton3)>200){ //change on button 2
    delay(5); //debounce
    if(abs(analogRead(BUTTON_PIN_3)-prevButton3)>200) prevButton3=analogRead(BUTTON_PIN_3);
    if(prevButton3<100){//button pressed down
      controlChange(MIDI_CHANNEL,2,127);
      //noteOn(MIDI_CHANNEL,LOWEST_NOTE+3,127);
      MidiUSB.flush();
      Serial.println("3");
    }
    if(prevButton3>800){ //button up
      controlChange(MIDI_CHANNEL,2,0);
      MidiUSB.flush();
    }
  }
  
  byte rot0;
  rot0 = rotary.rotate();
  if(rot0!=0){ //if not zero then there is movement on rotary 1=CW 2=CCW
    if (rot0==1){
      Serial.println("CW");
      if (vollev < 127) vollev++;
      controlChange(MIDI_CHANNEL,7,vollev);
      //LOWEST_NOTE = LOWEST_NOTE + 5;
    }
    else if (rot0==2){
      Serial.println("CCW");
      if (vollev > 0) vollev=vollev-1;
      controlChange(MIDI_CHANNEL,7,vollev);
      //LOWEST_NOTE = LOWEST_NOTE - 5;
    }
    MidiUSB.flush();
  }
  
  debouncerR.update();
  debouncer0.update();
  debouncer1.update();
  debouncer2.update();
  debouncer3.update();
  if (debouncerR.fell()){
    controlChange(MIDI_CHANNEL,6,127);
    //noteOn(MIDI_CHANNEL,LOWEST_NOTE,127);
    MidiUSB.flush();
    Serial.println("R");
  }
  if (debouncerR.rose()){
    controlChange(MIDI_CHANNEL,6,0);
    //noteOff(MIDI_CHANNEL,LOWEST_NOTE,0);
    MidiUSB.flush();
  }
  if (debouncer0.fell()){
    controlChange(MIDI_CHANNEL,5,127);
    //noteOn(MIDI_CHANNEL,LOWEST_NOTE+1,127);
    MidiUSB.flush();
    Serial.println("0");
  }
  if (debouncer0.rose()){
    controlChange(MIDI_CHANNEL,5,0);
    //noteOff(MIDI_CHANNEL,LOWEST_NOTE+1,0);
    MidiUSB.flush();
  }
  if (debouncer1.fell()){
    controlChange(MIDI_CHANNEL,4,127);
    //noteOn(MIDI_CHANNEL,LOWEST_NOTE+2,127);
    MidiUSB.flush();
    Serial.println("1");
  }
  if (debouncer1.rose()){
    controlChange(MIDI_CHANNEL,4,0);
    //noteOff(MIDI_CHANNEL,LOWEST_NOTE+2,0);
    MidiUSB.flush();
  }
  colorDISPLAY();
}

void colorDISPLAY(){ //outputs color for underglow
   for (int i=0;i<NUM_LEDS;i++){
      leds[i] = CRGB::White;
    }
   FastLED.show();
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, uint8_t(0x90 | channel), pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, uint8_t(0x80 | channel), pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}
