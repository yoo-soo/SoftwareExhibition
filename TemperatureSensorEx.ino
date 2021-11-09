#define TEMP_LM35 A0

void setup() {
  Serial.begin(9600);
}

void loop() {
  float temp_lm35 = (5.0*analogRead(TEMP_LM35)*100)/1024;
  Serial.print("온도 : "); 
  Serial.println(temp_lm35);
  delay(1000);
}
