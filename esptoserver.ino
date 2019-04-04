  //send data from esp to server using wifi(myfirstesp) for testing only
  // Libraries 
  #include <Wire.h>
  #include <ESP8266HTTPClient.h>
  #include<ESP8266WiFi.h>

  #define LDR_PIN                   A0     //analog pin
  #define MAX_ADC_READING           1023
  #define ADC_REF_VOLTAGE           3.3   // 3.3v for esp8266 4.96 for arduino
  #define REF_RESISTANCE            9860  // measure this for best results,this value is of 10k resistor
  #define LUX_CALC_SCALAR           12518931
  #define LUX_CALC_EXPONENT         -1.405
  void setup()
  {
    Serial.begin(115200);
    WiFi.begin("Who are you?","iamshekhar");  // add your ssid and password here
  
    while(WiFi.status() !=WL_CONNECTED)
    {
      delay(500);
      Serial.println("Waiting for connection");
    }
    
    Serial.println("Connected...");
    delay(1000);
  }
  
  void loop()
  {   int   ldrRawData;
      float resistorVoltage, ldrVoltage;
      float ldrResistance;
      float ldrLux;

      ldrRawData = analogRead(LDR_PIN);
  
      // RESISTOR VOLTAGE_CONVERSION
      // Convert the raw digital data back to the voltage that was measured on the analog pin
      resistorVoltage = (float)ldrRawData / MAX_ADC_READING * ADC_REF_VOLTAGE;
    
      // voltage across the LDR is the supply minus the resistor voltage
      ldrVoltage = ADC_REF_VOLTAGE - resistorVoltage;
      
      // LDR_RESISTANCE_CONVERSION
      // resistance that the LDR would have for that voltage  
      ldrResistance = ldrVoltage/resistorVoltage * REF_RESISTANCE;
      
      // LDR_LUX
      // Change the code below to the proper conversion from ldrResistance to
      // ldrLux
      ldrLux = LUX_CALC_SCALAR * pow(ldrResistance, LUX_CALC_EXPONENT);
  
      
   if (WiFi.status() ==WL_CONNECTED)
    {
      Serial.println("Wi-Fi Connected!"); 
    }
    delay(2000);
    Serial.println("Sending message to server espcomm");
    int res=sendmessage("Illumination_intensity_"+String(ldrLux));
    delay(2000);
    if (res==1)
    {
      Serial.println("Send Successfully");
      Serial.print(ldrLux);
    }
    else
    {
      Serial.println("Error on Server side or client side.");
    }
    delay(1000);
  }
  
  
  
  int sendmessage(String d)
  {
    int sres;
    int net;
    if (WiFi.status()==WL_CONNECTED)
    {
      HTTPClient http;
      String url="http://myfirstesp1.000webhostapp.com/writetxt.php?data="+d;
      http.begin(url);
      http.addHeader("Content-Type","text/plain");
      int httpCode=http.GET();
      String payload=http.getString();
      Serial.println("While sending I received this from server : "+payload);
      if (payload=="SUCCESS. Data written in file.")
      {
        sres=1;
      }
      else
      {
        sres=0;
      }
      http.end();
      net=1;
    }
    else
    {
      Serial.println("Internet Problem...");
      net=0;
    }
    return (net && sres);
  }
