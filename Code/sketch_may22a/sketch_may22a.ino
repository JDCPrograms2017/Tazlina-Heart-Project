#define touchPin T0
int touchValue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  touchValue = touchRead(T0);
  Serial.println(touchValue);
  
}
