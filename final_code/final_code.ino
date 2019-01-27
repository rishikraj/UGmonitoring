//temp35
int threshold_t=35;    
int tempPin = A0;
int led_t=10;

//smoke
int smokeA0=A1;
int threshold=500;
int led_s=12;
int buzz_pin=9;

//ldr
int sensorPin = A2; // select the input pin for LDR
int led_d=11;
int threshold_ldr=260;


void setup() {
 pinMode(led_t,OUTPUT);

 pinMode(led_s,OUTPUT);
 pinMode(buzz_pin,OUTPUT);

 pinMode(led_d,OUTPUT);
 
 Serial.begin(9600);

}

void loop() {
  //temp35 start
  float val=0;

  for(int i = 0; i < 10; i++) { // Average 10 readings for accurate reading
     val += analogRead(tempPin); 
     delay(20);
  }
  float mv = ( val/1023.0)*5000; 
  float cel = mv/200;


  Serial.print("TEMPRATURE = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();

  if(cel>threshold_t)
    digitalWrite(led_t,HIGH);
  else
    digitalWrite(led_t,LOW);
//temp35 end


//smoke start
 int analogSensor=0;
 analogSensor = analogRead(smokeA0);
 
 if(analogSensor>threshold){
 digitalWrite(led_s,HIGH);
 tone(buzz_pin, 1000, 200);}
 else{
 digitalWrite(led_s,LOW);
 noTone(buzz_pin);
 }
 Serial.print("SMOKE: ");
 Serial.print(analogSensor);
 Serial.println();
 //smoke end



 //ldr start
  int sensorValue=0;
  sensorValue = analogRead(sensorPin); 

  if(sensorValue<threshold_ldr)
  digitalWrite(led_d,HIGH);
  else
  digitalWrite(led_d,LOW);

  Serial.print("LDR: ");
  Serial.print(sensorValue);
  Serial.println();
  Serial.println();
//ldr end

delay(2000);

}
