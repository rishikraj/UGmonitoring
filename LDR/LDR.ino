int sensorPin = A2; // select the input pin for LDR
int led_d=11;
int sensorValue = 0; // variable to store the value coming from the sensor
void setup() {
  pinMode(led_d,OUTPUT);
  Serial.begin(9600); //sets serial port for communication
}
void loop() {
sensorValue = analogRead(sensorPin); // read the value from the sensor
Serial.println(sensorValue); //prints the values coming from the sensor on the screen
delay(100);

if(sensorValue<260)
digitalWrite(led_d,HIGH);
else
digitalWrite(led_d,LOW);
}
