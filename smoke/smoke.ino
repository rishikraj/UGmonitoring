int smokeA0=A1;
int threshold=100;
int led_s=12;
int buzz_pin=9;

void setup() {
  // put your setup code here, to run once:
 
 pinMode(led_s,OUTPUT);
 pinMode(buzz_pin,OUTPUT);
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
   int analogSensor=0;
 analogSensor = analogRead(smokeA0);
 
 if(analogSensor>threshold){
 digitalWrite(led_s,HIGH);
 tone(buzz_pin, 1000, 200);}
 else{
 digitalWrite(led_s,LOW);
 noTone(buzz_pin);
 }
 Serial.println(analogSensor);
 delay(500);
}
