//tEMP+HUMIDITY WITHOUT SCROLLING
//IMPLEMENTED BY EHSAN SUNY
//01757589636

#include <Wire.h>
#include <DHT11.h>
#include <LiquidCrystal.h>
#include "RTClib.h"

int pin=10;
DHT11 dht11(pin);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () 
{
for (int DigitalPin = 6; DigitalPin <= 9; DigitalPin++) 
 {
  pinMode(DigitalPin, OUTPUT);
 }
#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif
{
  lcd.begin(20,4);
}
  delay(3000); // wait for console opening

  if (! rtc.begin()) {
    lcd.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    lcd.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

}

void loop () {
    
   //*****************************************************TITLE OF THE PROJECT******************************************************************** 
     
     lcd.setCursor(0,0);
    lcd.print("TEMP+HUMI AUTOMATION");
   
   
    
    //******************************************************DATE AND TIME***************************************************************************
    lcd.setCursor(0,1); 
    DateTime now = rtc.now();
    
    lcd.print(now.year(), DEC);
    lcd.print('/');
    lcd.print(now.month(), DEC);
    lcd.print('/');
    lcd.print(now.day(), DEC);
    lcd.print("    ");
    
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    lcd.print(now.second(), DEC);
    

//*******************************************************TEMPERATURE & HUMIDITY*******************************************************************
  
    int err;
  float temp, humi;
  if((err=dht11.read(humi, temp))==0)
  {
    lcd.setCursor(0,2);
    lcd.print("T:");
    lcd.print(temp);
    lcd.print(char(223));
    lcd.print("C   ");
    lcd.print("H:");
    lcd.print(humi);
    lcd.print("%");
  }
 
  delay(DHT11_RETRY_DELAY); //delay for reread
//***********************************************************FROM THE TIME AFTER 6 PM********************************************* 
if (now.hour()>=18)
  {
    if ((temp<27)&&(humi>85))
    {
    digitalWrite (6, HIGH);
    digitalWrite (7, LOW);
    digitalWrite (8, LOW);
    digitalWrite (9, LOW);
    lcd.setCursor(0,3);
    lcd.print("Light: 3    ");
    lcd.print("Fan: 0");
    }
    else
    {
      digitalWrite (6, HIGH);
      digitalWrite (7, HIGH);
      digitalWrite (8, HIGH);
      digitalWrite (9, LOW);
    lcd.setCursor(0,3);
    lcd.print("Light: 1    ");
    lcd.print("Fan: 0");
    }
    }
  
//******************************************************AT THE TIME AFTER 12AM/00AM***********************************
  else if (now.hour()<9)
  {
    if ((temp<27)||(humi>85))
    {
  digitalWrite (6, HIGH);
    digitalWrite (7, LOW);
    digitalWrite (8, LOW);
    digitalWrite (9, LOW);
      lcd.setCursor(0,3);
    lcd.print("Light: 3    ");
    lcd.print("Fan: 0");
    }
    else
    {
       digitalWrite (6, HIGH);
      digitalWrite (7, HIGH);
      digitalWrite (8, HIGH);
      digitalWrite (9, LOW);
        lcd.setCursor(0,3);
    lcd.print("Light: 1    ");
    lcd.print("Fan: 0");
    }
    }
     
    
//*************************************************FROM THE TIME 9AM***************************************

     else if (now.hour()>=9)
      {
        if ((temp>30)&& (humi<88))
         {
      digitalWrite (6, LOW);
      digitalWrite (7, HIGH);
      digitalWrite (8, HIGH);
      digitalWrite (9, HIGH);
      lcd.setCursor(0,3);
    lcd.print("Light: 0    ");
    lcd.print("Fan: 1");
        }
       else if ((temp<27) && (humi>65))
         {
      digitalWrite (6, HIGH);
      digitalWrite (7, LOW);
      digitalWrite (8, HIGH);
      digitalWrite (9, LOW);
      lcd.setCursor(0,3);
    lcd.print("Light: 2    ");
    lcd.print("Fan: 0");
        }
         else
      {
         {
      digitalWrite (6, HIGH);
      digitalWrite (7, HIGH);
      digitalWrite (8, HIGH);
      digitalWrite (9, HIGH);
    lcd.setCursor(0,3);
    lcd.print("Light: 0    ");
    lcd.print("Fan: 0");
    }
      }
      }
      else
      {
         {
      digitalWrite (6, HIGH);
      digitalWrite (7, HIGH);
      digitalWrite (8, HIGH);
      digitalWrite (9, HIGH);
       lcd.setCursor(0,3);
    lcd.print("Light: 0    ");
    lcd.print("Fan: 0");
    }
      }
}
