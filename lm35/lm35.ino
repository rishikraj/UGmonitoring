
#include <OneWire.h>
#include <DallasTemperature.h>
  float temp=A0;
  int led_t=11;
  int smokeA1=A1;
  int threshold=400;
  int led_s=12;
  
  void setup() {
  
  pinMode(led_t, OUTPUT);
  pinMode(led_s,OUTPUT);
  Serial.begin(9600);
 
}

void loop() {
 
  temp=analogRead(A0);
  temp=(temp * 0.048820)-20;
  int analogSensor = analogRead(smokeA1);

  Serial.println(temp);
  delay(1000);
  if(temp>10)
  digitalWrite(led_t,HIGH);

 
  if(analogSensor>threshold)
  digitalWrite(led_s,HIGH);
  Serial.println(analogSensor);
  delay(500);
}
