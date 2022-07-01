#define BLYNK_PRINT Serial   
#define BLYNK_TEMPLATE_ID "TMPL6Rg5FGDO"
#define BLYNK_DEVICE_NAME "Smart Plant Monitoring System"
#define BLYNK_AUTH_TOKEN "tLAQAcXtOVl6jKaQrjyTFlamxFyy4JMY"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;             //Authentication code sent by Blynk
char ssid[] = "Vithika";                       //WiFi SSID
char pass[] = "Vithika123";  
//WiFi Password
int button;

#define relayPin D1 
#define DHTPIN 14  
#define DHTTYPE DHT11     
DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
 
  //Serial.println("Temperature is: ");
  //Serial.println(t);
  //Serial.println("Humidity is: ");
  //Serial.println(h);
  Blynk.virtualWrite(V5, h);  //V5 is for Humidity
  Blynk.virtualWrite(V6, t);  //V6 is for Temperature
}
    BLYNK_WRITE(V0){
    button= param.asInt();
    
    }
   //roshita
void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensor);
  pinMode(relayPin, OUTPUT);
  dht.begin();
  sensors.begin();
}
void loop()
{
  Blynk.run(); 
  timer.run(); 
  
  int sensor=analogRead(A0);
  Blynk.virtualWrite(V2, sensor);
  
  Serial.println(sensor);
 
  if(sensor >= 800)  //dry- Blue tak immerse soil mositure sensors
  {
    digitalWrite(relayPin, HIGH);
    Serial.println(sensor);
    Serial.println(digitalRead(relayPin));
 
  } 
  if(sensor < 800 && sensor >400)  //dry- Blue tak immerse soil mositure sensors
  {
    digitalWrite(relayPin, button);
    Serial.print(button);
    Serial.println(digitalRead(relayPin));
  }
  if(sensor <=400) //wet
  {
    digitalWrite(relayPin, LOW);
    Serial.println(sensor);
    Serial.println(digitalRead(relayPin));
    
  }
  delay(1000);
