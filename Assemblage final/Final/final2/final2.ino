#include <LiquidCrystal.h>
#include <Keypad.h>
#include  <Wire.h>
#include <SeeedOLED.h>
#include  "rgb_lcd.h"
#include "DHT.h"
#define DHTPIN 8
#define DHTTYPE DHT22

rgb_lcd  lcd;

//Partie Corentin
char Clavier[5];
int compteur = 0;
int N;
int M1 = 2;            
int code;
const byte ROWS = 4; 
const byte COLS = 3;
const int C3=11; 
const int C2=13; 
const int C1=15; 
const int L4=3;
const int L3=5;
const int L2=7; 
const int L1=9; 
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = { 9, 7, 5, 3}; 
byte colPins[COLS] = {15, 13, 11}; 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
char key;

//Partie Alexis
DHT dht(DHTPIN, DHTTYPE);

//partie Jonathan
int RELAY = 14;
int RELAY2 = 18;
int SmokeSensor = A2;
int SmokeSensorVal = 0;

int dangercheck = 500;

static const unsigned char SeeedLogo[] PROGMEM = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x1f, 
  0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 
  0x3f, 0x1f, 0x1f, 0x0f, 0x0f, 0x0f, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x03, 0x03, 0x01, 
  0x01, 0x01, 0x01, 0x00, 0x30, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x18, 0x18, 0x10, 0x10, 0x10, 0x10, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x46, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x63, 0x43, 0x43, 0x42, 0xc2, 0x82, 0x82, 0x86, 0x84, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x0c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x18, 0x18, 0x10, 0x10, 0x10, 0x10, 0x20, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x80, 0x80, 0xc0, 0xc0, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf4, 0xf4, 0xbc, 0xa0, 0xa0, 0xa0, 0x60, 0x40, 0x40, 0x40, 
  0x80, 0x80, 0x90, 0x80, 0x00, 0x00, 0x00, 0x20, 0x00, 0x60, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x80, 0xd0, 0xc8, 0xe8, 0xe4, 0xf6, 0xfa, 0xfb, 
  0xfd, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 
  0xfe, 0xfe, 0xfe, 0xfc, 0xfd, 0xfd, 0xfd, 0xf8, 0xfa, 0xfa, 0xf0, 0xf0, 0xf4, 0xf4, 0xe4, 0xf4, 
  0xe0, 0xe0, 0xf0, 0xf8, 0xf8, 0xfc, 0xfd, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

void setup(){
   Wire.begin();
   SeeedOled.init();
   SeeedOled.clearDisplay();
   SeeedOled.setNormalDisplay();
   SeeedOled.setPageMode();
   SeeedOled.drawBitmap((unsigned char*) SeeedLogo, 1024);

   
   lcd.begin(16, 2);
   lcd.setRGB(0, 0, 220);

//Partie Corentin
 pinMode(M1, OUTPUT);    
   
//Partie Alexis
dht.begin();
   
pinMode(4,OUTPUT);
pinMode(6,OUTPUT);
pinMode(10,OUTPUT);
pinMode(12,OUTPUT);

//Partie Jonathan
pinMode(RELAY, OUTPUT); // Relay
pinMode(RELAY2, OUTPUT); // Relay2
pinMode(SmokeSensor, INPUT); // SmokeSensor
}
  
void loop(){
   Corentin();
}

//Jonathan
void Jonathan() {
      SmokeSensorVal = analogRead(SmokeSensor);

      SeeedOled.setTextXY(0, 0);
      SeeedOled.putString("fumee :");
      SeeedOled.setTextXY(0, 8);
      SeeedOled.putNumber(SmokeSensorVal);

      if(SmokeSensorVal > dangercheck) {
   JonathanAff(false);
      } else {
   JonathanAff(true);
      }
}

void JonathanAff(boolean etat) {
      if(etat == true) {
   digitalWrite(RELAY, LOW);
   digitalWrite(RELAY2, LOW);
      } else {
   SeeedOled.setTextXY(1, 0);
   SeeedOled.putString("Fumee Detectee");
   digitalWrite(RELAY, HIGH);
   digitalWrite(RELAY2, HIGH);
      }
 }
 
 //Alexis
 void AlexisHumi() {
   float humi = dht.readHumidity();
 
   if (humi>47.5) { digitalWrite(4,HIGH); }
   if (humi<45) { digitalWrite(4,LOW); }
   if (humi>35) { digitalWrite(6,LOW); }
   if (humi<32.5) { digitalWrite(6,HIGH); }

   SeeedOled.setTextXY(3, 0);
   SeeedOled.putString("humi :   ");   
   SeeedOled.setTextXY(3, 8);
   SeeedOled.putFloat(humi);
 }
 
 void AlexisTemp() {
   float temp = dht.readTemperature();
   
   if (temp<25) { digitalWrite(10,HIGH); }
   if (temp>26) { digitalWrite(10,LOW); }
   if (temp>27) { digitalWrite(12,HIGH); }
   if (temp<25.5) { digitalWrite(12,LOW); }
   
   SeeedOled.setTextXY(4, 0);
   SeeedOled.putString("temp :    ");
   SeeedOled.setTextXY(4, 8);
   SeeedOled.putFloat(temp);
 }
 
 //Corentin
 void Corentin() {   
   while(N != 4) {    
      lcd.setCursor(0, 0);
      lcd.print("Code:");  
      key = keypad.getKey();
      if (key){ 
        if(key != '#') {
          CorentinCheck();
        } else {
          Affichage();
        }
      }
   }
   lcd.setCursor(0, 0);
   if (code == 3894 ){
      lcd.print("Code Correct          ");
      digitalWrite(M1,HIGH);
      lcd.setRGB(0, 255, 0);
      delay(5000);
      lcd.setRGB(0, 0, 220);
      digitalWrite(M1,LOW);
      CorentinReset();
   }else{
      lcd.print("Code Incorrect         ");
      lcd.setRGB(255, 0, 0);
      delay(1000);
      lcd.setRGB(0, 0, 220);
      CorentinReset();
   }
 }
 
 void CorentinCheck() {
      Clavier[compteur++]= key;
      Clavier[compteur]= '\0';
      code= atoi(Clavier);  
      lcd.setCursor(8, 0);
      lcd.print("*");
      delay(100);
      N=1+N; 
 }
 
 void CorentinReset() {
   delay(500);
   lcd.setCursor(0, 0);
   lcd.print("              ");
   N=0; 
   compteur =0;
   delay(1000);
   Corentin();
 }

 void Affichage() {
  SeeedOled.clearDisplay();
  Jonathan();
  AlexisHumi();
  AlexisTemp();
 }

