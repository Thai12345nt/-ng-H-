//Tác Giả: Trương Hữu Quốc Thái
//Ngày : 19/7/2022

//khai báo thư viện
#include <Wire.h>
#include <LiquidCrystal.h>
#include "RTClib.h"
#include "DHT.h"            

//khai báo chân kết nối DHT11
const int DHTPIN = 10 ;      
const int DHTTYPE = DHT11;  

//khởi chạy DHT
DHT dht(DHTPIN, DHTTYPE);

//Khởi chạy DS1307
RTC_DS1307 rtc;
// Khởi chạy lcd
LiquidCrystal lcd( 4, 5, 6, 7, 8, 9  );

int t=0 ; 
//khia báo ngày
char daysOfTheWeek[7][12] = {"CNhat", "Thu2", "Thu3", "Thu4", "Thu5", "Thu6", "Thu7"};

void setup () 
{
  Serial.begin(9600);  //set cổng 9600
  lcd.begin(16,2);     //chạy lcd
  dht.begin();         // chạy DHT

  //kiểm tra DS1307 có chạy không
  if (! rtc.begin()) 
  {
    lcd.print("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) 
  {
    lcd.print("RTC is NOT running!");
  }
  
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));//lấy thời gian từ máy tính
    //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));// tự set thời gian 
    //bạn có thể bỏ hai dòng này nếu lấy thời gian có sẵn trong DS1307
}

void loop () 
{
  //lấy giời
    DateTime now = rtc.now();
  //lấy nhiệt độ độ ẩm từ DHT11
  float h = dht.readHumidity();    
  float t = dht.readTemperature(); 

  
//  lcd.setCursor(9,0);

//hiện thị lcd
    
    lcd.setCursor(0, 0);
    
    if(now.hour()<=9)
    {
      lcd.print("0");
      lcd.print(now.hour());
    }
     else {
     lcd.print(now.hour()); 
    }
    lcd.print(':');
    
    if(now.minute()<=9)
    {
      lcd.print("0");
      lcd.print(now.minute());
    }
    else {
     lcd.print(now.minute()); 
    }
    lcd.print(':');
    
    if(now.second()<=9)
    {
      lcd.print("0");
      lcd.print(now.second());
    }
    else {
     lcd.print(now.second()); 
    }
    lcd.print("  ");
    
    lcd.print(t);

    
    lcd.print("C");
    

    lcd.setCursor(0,1);
    
    lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
    lcd.setCursor(6,1);
    
    if(now.day()<=9)
    {
      lcd.print("0");
      lcd.print(now.day());
    }
    else {
     lcd.print(now.day()); 
    }
    lcd.print('/');
    if(now.month()<=9)
    {
      lcd.print("0");
      lcd.print(now.month());
    }
    else {
     lcd.print(now.month()); 
    }
    lcd.print('/');
    if(now.year()<=9)
    {
      lcd.print("0");
      lcd.print(now.year());
    }
    else {
     lcd.print(now.year()); 
    }


}
