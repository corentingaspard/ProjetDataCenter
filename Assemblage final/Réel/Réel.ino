#include <LiquidCrystal.h>
#include <Keypad.h>
#include  <Wire.h>
#include  "rgb_lcd.h"
#include "DHT.h"
#define DHTPIN 8
#define DHTTYPE DHT22

rgb_lcd  lcd;

int etape;

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
//int BUZZER = 4;
int dangercheck = 300;

void setup(){

   lcd.begin(16, 2);
   lcd.setRGB(0, 0, 255);

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

etape=1;
lcd.setCursor(0, 1);
lcd.print("                              ");
}
  
void loop(){
   Corentin();
}

//Jonathan
void Jonathan() {
      int sensorValue = analogRead(A2);  

      lcd.setCursor(0, 1);
      lcd.print("fumee :");
      lcd.setCursor(8, 1);
      lcd.print(sensorValue);

      if(sensorValue > dangercheck) {
   JonathanAff(false);
      } else {
   JonathanAff(true);
      }
}

void JonathanAff(boolean etat) {
      if(etat == true) {
   digitalWrite(RELAY, LOW);
      } else {
   lcd.setCursor(0, 1);
   lcd.print("Fumee Detectee                             ");
   digitalWrite(RELAY, HIGH);
      }
 }
 
 //Alexis
 void AlexisHumi() {
   float humi = dht.readHumidity();
 
   if (humi>47.5) { digitalWrite(4,HIGH); }
   if (humi<45) { digitalWrite(4,LOW); }
   if (humi>35) { digitalWrite(6,LOW); }
   if (humi<32.5) { digitalWrite(6,HIGH); }

   lcd.setCursor(0, 1);
   lcd.print("humi :   ");   
   lcd.setCursor(8, 1);
   lcd.print(humi);
 }
 
 void AlexisTemp() {
   float temp = dht.readTemperature();
   
   if (temp<25) { digitalWrite(10,HIGH); }
   if (temp>26) { digitalWrite(10,LOW); }
   if (temp>27) { digitalWrite(12,HIGH); }
   if (temp<25.5) { digitalWrite(12,LOW); }
   
   lcd.setCursor(0, 1);
   lcd.print("temp :    ");
   lcd.setCursor(8, 1);
   lcd.print(temp);
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
      if(etape == 3) {
         etape=0;
         lcd.setCursor(0, 1);
         lcd.print("                              ");
         AlexisTemp();
         return;
      }
      if(etape == 2) {
         etape=etape+1;
         lcd.setCursor(0, 1);
         lcd.print("                              ");
         AlexisHumi();
      }
      if(etape == 1) {
         etape=etape+1;
         lcd.setCursor(0, 1);
         lcd.print("                              ");
         Jonathan();
      }
      if(etape == 0) {
         etape=etape+1;
         lcd.setCursor(0, 1);
         lcd.print("                              ");
      }
   }
      }
   }
   lcd.setCursor(0, 0);
   if (code == 3894 ){
      lcd.print("Code Correct          ");
      digitalWrite(M1,HIGH);
      delay(5000);
      digitalWrite(M1,LOW);
      CorentinReset();
   }else{
      lcd.print("Code Incorrect         ");
      delay(1000);
      CorentinReset();
   }
 }
 
 void CorentinCheck() {
      Clavier[compteur++]= key;
      Clavier[compteur]= '\0';
      code= atoi(Clavier);  
      lcd.setCursor(8, 0);
      lcd.print(key);
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

