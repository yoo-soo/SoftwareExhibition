#define A0Pin 0
int A_1A = 11; // 모터드라이브 A_1A 핀 변수 선언
int A_2A = 12; // 모터드라이브 A_1B 핀 변수 선언
int needWater = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(A_1A, OUTPUT); // 모터드라이브 A_1A의 pinMode 선언
  pinMode(A_2A, OUTPUT); // 모터드라이브 A_1B의 pinMode 선언 
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  needWater = analogRead(A0Pin); // 토양습도센서 센서값 읽어서 저장
  delay(1000);
  Serial.print("Asensor = ");
  Serial.println(needWater); // dry(0) ~ wet(1023) 값 출력

  if(needWater <= 400){ // 토양 습도 데이터가 400 이하이면
    pump(1); // 워터펌프 작동 함수 실행
    digitalWrite(6, HIGH); // 워터펌프가 작동할 때 pin6 RED LED 켜짐
    digitalWrite(5, LOW); // 워터펌프가 작동할 때 BLUE LED가 켜져있다면 끄기
  }
  else if(needWater > 400){ // 토양 습도 데이터가 400 초과이면 
    digitalWrite(5, HIGH); // 워터펌프가 작동하지 않을 때 pin5 BLUE LED 켜짐
    digitalWrite(6, LOW); // 워터펌프가 작동하지 않을 때 RED LED가 켜져있다면 끄기
  } 
}

void pump(int flag){ // 펌프 작동 함수
  boolean inPin1 = HIGH;
  boolean inPin2 = LOW;

  if(flag == 1){ // flag가 1이면
    inPin1 = HIGH; 
    inPin2 = LOW;
  }

  digitalWrite(A_1A, inPin1); // 펌프 A_1A에 write
  digitalWrite(A_2A, inPin2); // 펌프 A_1B에 wrtie
  delay(1000); // 1초 동안 물주기
  stop();
}

// 워터펌프 물주기 멈춤 함수.
void stop(){
  digitalWrite(A_1A, LOW);
  digitalWrite(A_2A, LOW);
}
