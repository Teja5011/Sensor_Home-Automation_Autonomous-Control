#include <Wire.h>
#include <EEPROM.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTPIN 2 
#define DHTTYPE DHT11 
DHT dht(DHTPIN,DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS1307 RTC;
int temp, inc, hours1, minut, add = 11;
int next = A0;
int INC = A1;
int set_mad = A2;
int ir1=3;
int ir2=4;
int ir3=6;
int ldr=A3;
int fan3=5;
int HOUR,MINUT, SECOND;
int light1=7;
int light2=8;
int fan1=9;
int fan2=10;
int light3=11;
int ac2=12;
int led=13;
int kk=0;
void setup() {
  Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  lcd.begin(); // LCD screen initialization
  lcd.backlight();
  dht.begin();
  pinMode(ir1,INPUT);
  pinMode(ir2,INPUT);
  pinMode(ir3,INPUT);
  pinMode(ldr,INPUT);
  pinMode(INC,INPUT);
  pinMode(next,INPUT);
  pinMode(set_mad,INPUT);
  pinMode(light1,OUTPUT);
  pinMode(light2,OUTPUT);
  pinMode(fan1,OUTPUT);
  pinMode(fan2,OUTPUT);
  pinMode(fan3,OUTPUT);
  pinMode(light3,OUTPUT);
  pinMode(ac2,OUTPUT);
  pinMode(led,OUTPUT);
  digitalWrite(light1,1);
  digitalWrite(light2,1);
  digitalWrite(fan1,0);
  digitalWrite(fan2,0);
  digitalWrite(light3,1);
  digitalWrite(ac2,1);
  digitalWrite(led,0);
   lcd.setCursor(0, 0);
  lcd.print("Smart  Home");
  lcd.setCursor(0, 1);
  lcd.print("Using Arduino");
  delay(2000);
  if (!RTC.isrunning()) {
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}
void loop() {
  DateTime now = RTC.now();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time:");
  lcd.setCursor(6, 0);
  lcd.print(HOUR = now.hour(), DEC);
  lcd.print(":");
  lcd.print(MINUT = now.minute(), DEC);
  lcd.print(":");
  lcd.print(SECOND = now.second(), DEC);
  int ival1 = digitalRead(ir1);
  int ival2 = digitalRead(ir2);
  int ival3 = digitalRead(ir3);
  int lval = analogRead(ldr);
 // int temp =0, val = 1, temp4;
  int t = dht.readTemperature();
  int h=dht.readHumidity();
  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.print(t);
  lcd.setCursor(9, 1);
  lcd.print("l: ");
  lcd.setCursor(11, 1);
  lcd.print(lval);
  delay(300);
  if(lval>600 )
   {
     kk=1;
    if(ival2==0)
    {
      digitalWrite(light1,0);
    }
    else
    {
       digitalWrite(light1,1);
    }
    if(ival1==0)
   {
     digitalWrite(light2, 0);
   }
    else
    {
       digitalWrite(light2,1);
    }
   if(ival3==0)
   {
     digitalWrite(light3,0);
   }
   else 
    {
    digitalWrite(light3,1);
   }
  }
  if(t<31)
  { 
    
    if (ival1==0)
    {
      analogWrite(fan1,150);
    }
    else 
  {
    digitalWrite(fan1,0);
 
  }
  if (ival2==0)
  {  
  analogWrite(fan2,150);
  }
  else 
  {
    digitalWrite(fan2,0);
  }
  if (ival3==0)
  {
     analogWrite(fan3,150);
  }
  else 
  {
    digitalWrite(fan3,0);
  }
  }
  if(t>33)
  {
    if (ival1==0)
    {
     analogWrite(fan1,200);
    }
    else 
  {
    digitalWrite(fan1,0);
  }
    if (ival2==0)
  {   
  analogWrite(fan2,200);
  }
  else 
  {
    digitalWrite(fan2,0);
  }
  if (ival3==0)
  {
     analogWrite(fan3, 200);
  }
  else 
  {
    digitalWrite(fan3,0);
  }
  }
  if (t>37)
  {
     //digitalWrite(ac1,0);
     digitalWrite(ac2,0);
  }
   else 
  {
    //digitalWrite(ac1,1);
    digitalWrite(ac2,1);
    
  }
   if (digitalRead(set_mad) == 0) 
   {
    lcd.setCursor(0, 0);
    lcd.print("Set Medicine");
    lcd.setCursor(0, 1);
    lcd.print("Reminder Time");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Time 1");
    defualt();
    time(1);
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Time 2");
    defualt();
    delay(1000);
    time(2);
  }
 match();

  delay(200);
}

void defualt() {
  lcd.setCursor(0, 1);
  lcd.print(HOUR);
  lcd.print(":");
  lcd.print(MINUT);
  lcd.print(":");
  lcd.print(SECOND);
}

void time(int x) {
  int temp = 1, minuts = 0, hours = 0, seconds = 0;
  while (temp == 1) {
    if (digitalRead(INC) == 0) {
      HOUR++;
      if (HOUR == 24) {
        HOUR = 0;
      }
      while (digitalRead(INC) == 0);
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Time ");
    lcd.print(x);
    lcd.setCursor(0, 1);
    lcd.print(HOUR);
    lcd.print(":");
    lcd.print(MINUT);
    lcd.print(":");
    lcd.print(SECOND);
    delay(100);
    if (digitalRead(next) == 0) {
      hours1 = HOUR;
      EEPROM.write(add++, hours1);
      temp = 2;
      while (digitalRead(next) == 0)
        ;
    }
  }

  while (temp == 2) {
    if (digitalRead(INC) == 0) {
      MINUT++;
      if (MINUT == 60) {
        MINUT = 0;
      }
      while (digitalRead(INC) == 0);
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Time  ");
    lcd.print(x);
    lcd.setCursor(0, 1);
    lcd.print(HOUR);
    lcd.print(":");
    lcd.print(MINUT);
    lcd.print(":");
    lcd.print(SECOND);
    delay(100);
    if (digitalRead(next) == 0) {
      minut = MINUT;
      EEPROM.write(add++, minut);
      temp = 0;
      while (digitalRead(next) == 0)
        ;
    }
  }

  delay(1000);
}
void match() {
  int tem[17];
  for (int i = 11; i < 17; i++) {
    tem[i] = EEPROM.read(i);
  }
 if (HOUR == tem[11] && MINUT == tem[12]&& kk==1 ) 
 {  digitalWrite(light1, 1);
    digitalWrite(light2, 1);
    digitalWrite(light3, 1);
     lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Time Up");
    lcd.setCursor(0, 1);
    lcd.print("lights off");
   
     digitalWrite(led,1);
  

   
  }
  if (HOUR == tem[13] && MINUT == tem[14] ) {
    kk=0; 
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  TIMER-2  ");
     digitalWrite(led,0);
    
  }
}
