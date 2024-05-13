#include <Adafruit_NeoPixel.h>

#define neoPixel_1 2
#define ledCount 8
int potVal=0;
int pot2Val = 0;
int nLED = 0;
int wLED = 0;
bool debug = false;

Adafruit_NeoPixel strip(ledCount, neoPixel_1, NEO_GRB + NEO_KHZ800);

uint32_t magenta = strip.Color(255, 0, 255);
uint32_t yellow = strip.Color(255, 160, 0);
uint32_t green = strip.Color(55, 255, 5);
uint32_t red = strip.Color(255, 5, 0);
uint32_t blue = strip.Color(10, 10, 255);
uint32_t off = strip.Color(0, 0, 0);



void setup(){
  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(64);
  strip.show();
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void loop(){
  potVal = analogRead(A0);
  pot2Val = analogRead(A1);
  nLED = map(potVal,0,1023,0,7); //number of middle LED
  wLED = map(pot2Val,0,1023,0,4); //width of LEDs
  for(int i=0; i<wLED; i++){
    strip.setPixelColor((nLED+i),magenta);
    strip.setPixelColor((nLED-i),magenta);
  }
  strip.show();
  strip.fill(off, 0, 8);
  if(debug==true){
    Serial.print("nLED: ");
    Serial.println(nLED);
    Serial.print("wLED: ");
    Serial.println(wLED);
  }
}
