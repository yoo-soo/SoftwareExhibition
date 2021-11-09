#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define rxPin 2
#define txPin 3

LiquidCrystal_I2C lcd(0x27, 16, 2); // SDA = A4, SCL = A5
SoftwareSerial SwSerial(rxPin, txPin);

int red = 9, blue = 10; // 삼색 led
int cs = A0; // 온도센서
char data;

void setup() {
  // put your setup code here, to run once:
  analogReference(INTERNAL);
  Serial.begin(9600);
  SwSerial.begin(9600);
  //Serial.println("Ready..");
  
  lcd.init(); // LCD 초기설정
  lcd.backlight(); // LCD 초기설정
  
}

void loop() {
  // put your main code here, to run repeatedly:
// 블루투스 세팅
 /* Serial.flush();
  Serial.print("cmd : "); 
  
  while (!Serial.available());
  
  while (Serial.available()) { 
     data = Serial.read();   
     if(data == -1) break ; 
     
     SwSerial.print(data); 
     Serial.print(data);
     
      delay(1); // 시리얼 통신에서는 9600bps 기준으로 read 를 사용할 때 1ms 의 딜레이를 줘야 한다. 
  }
  
  Serial.println();
  delay(1000); // HC-06에서 처리할 시간을 준다 
  Serial.print("return : ");
  
  while (SwSerial.available()) {
     data = SwSerial.read();
  
      if(data == -1) break ; 
      
      Serial.print(data); 
      delay(1);
  }

  Serial.println(""); 
*/
// RGB LED
// 블루투스 연동
  if(SwSerial.available()) {
    char cmd = (char)SwSerial.read();
    if(cmd == '1') {
      analogWrite(red, 200);
      analogWrite(blue, 200);
    } else if(cmd == '0') {
      analogWrite(red, -1);
      analogWrite(blue, -1);
    }
  }

   analogWrite(red, 200);
   analogWrite(blue, 200);

// 온도센서 판판한곳 바라보고 왼쪽이 + 젤 오른쪽이 -   
  float temperature = analogRead(cs) / 9.31;
  Serial.print("Temperature = "); Serial.print(temperature); Serial.println(" degrees C");
  delay(1000);
// 블루투스 연동
  SwSerial.print("Temperature = "); SwSerial.print(temperature); SwSerial.println(" degrees C");
  delay(1000);
  
// LCD
   lcd.setCursor(0,0); //텍스트가 LCD에 나타날 위치
   lcd.print("soil water : ");

}
