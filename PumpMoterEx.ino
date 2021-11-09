int A_1A = 11; // 모터드라이브 A_1A 핀 변수 선언
int A_2A = 12; // 모터드라이브 A_1B 핀 변수 선언

void setup() {
  // put your setup code here, to run once:
  pinMode(A_1A, OUTPUT); // 모터드라이브 A_1A의 pinMode 선언
  pinMode(A_2A, OUTPUT); // 모터드라이브 A_1B의 pinMode 선언 
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*  if(SwSerial.available()) {
    char cmd = (char)SwSerial.read();
    if(cmd == '1') { // 시리얼 모니터에 water on 입력 시 
      pump(1); // pump 함수 호출
    } else if(cmd == '0') { // 시리얼 모니터에 water stop 입력 시
      stop();
    }
    delay(1000);
  }
  */
  char data = Serial.read();
  if (data == '1') {
    Serial.println(data);
    pump(1);
    
  }
  else if(data == '0') {
    Serial.println(data);
    stop();
  }

}

void pump(int flag){
  boolean inPin1 = HIGH;
  boolean inPin2 = LOW;

  if(flag == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  digitalWrite(A_1A, inPin1); // 펌프 A_1A에 write
  digitalWrite(A_2A, inPin2); // 펌프 A_1B에 wrtie
  delay(1000);
  stop();
}

void stop(){
  digitalWrite(A_1A, LOW);
  digitalWrite(A_2A, LOW);
}
