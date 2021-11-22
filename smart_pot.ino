#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define rxPin 2 // 블루투스센서 수신 보내는 핀
#define txPin 3 // 블루투스센서 수신 받는 핀

LiquidCrystal_I2C lcd(0x27, 16, 2); // SDA = A4, SCL = A5
SoftwareSerial SwSerial(rxPin, txPin);

int red = 9, blue = 10; // 삼색 led
int cs = A0; // 온도센서
char data;

void setup() {
  // put your setup code here, to run once:
  analogReference(INTERNAL);  // ADC 참조 전압 1.1V
  Serial.begin(9600);
  SwSerial.begin(9600);
  //Serial.println("Ready..");
  
  lcd.init(); // LCD 초기설정
  lcd.backlight(); // LCD 초기설정
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
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
    char cmd = (char)SwSerial.read(); // 블루투스 시리얼에서 데이터 읽음
    
    if(cmd == '1') {  // 블루투스 시리얼에 1이 들어오면
      Serial.println(cmd);
      digitalWrite(red, HIGH);
      digitalWrite(blue, HIGH);
      // 불 킴
    } else if(cmd == '0') { // 블루투스 시리얼에 0이 들어오면
      digitalWrite(red, LOW);
      digitalWrite(blue, LOW);
      // 불 끔
    }
  }   

// 온도센서 판판한곳 바라보고 왼쪽이 + 젤 오른쪽이 -   
  float temperature = analogRead(cs) / 9.31;  // 온도 센서로 온도 읽고 9.31로 나누기 (섭씨로 표현하기 위해)
  
// LCD
   lcd.setCursor(0,0); // 텍스트가 LCD에 나타날 위치
   lcd.print("Temperature : "); 
   lcd.print(temperature);
   lcd.setCursor(0,1); 
   lcd.print("Sensing...");

}
