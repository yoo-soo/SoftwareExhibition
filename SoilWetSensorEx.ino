#define A0Pin 0
int sensorVal = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorVal = analogRead(A0Pin); // 토양습도센서 센서값 읽어서 저장
  delay(1000);
  Serial.print("Asensor = ");
  Serial.println(sensorVal); // dry(0) ~ wet(1023) 값 출력
  
}
