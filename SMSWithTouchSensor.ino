#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> //include library
const char* ssid = "iPhone";
const char* password = "caiyanRU666";//connected to the WiFi
const char* host = "maker.ifttt.com";
const char* apiKey = "bdDBujcGlLVdpDsRJmBanu"; //the "token" to access the web page
int sensorPin = D0; // Pin connected to the touch sensor
int LEDPin=D1;       //Pin connected to the LED
int flag=0;          //serves as a mark
unsigned long startTime;
unsigned long stopTime;
unsigned long elapsedTime; //to calculate the duration 
 int count=0;
void setup() {
   Serial.begin(115200);
   Serial.println("Touch sensor integration with IFTTT");
   delay(100);
   Serial.print("Connecting to ");
   Serial.println(ssid);
   WiFi.begin(ssid, password); //try to connect to WiFi
   while (WiFi.status() != WL_CONNECTED)
   {
   delay(500);
   Serial.print(".");
   Serial.println("");
    Serial.println("IP address: "); //get IP address when connected
    Serial.println(WiFi.localIP());  
  //from website
  pinMode(D0, INPUT);
 pinMode(D1, OUTPUT);
 }
 
}

void loop()
{
 if(flag==0&&digitalRead(sensorPin) == HIGH)
  { startTime = millis(); 
    Serial.println("start time=");
    Serial.println(startTime);
    Serial.println("ms");
    Serial.println();
    delay(500);
    
    flag=1; 
  } 
  if (flag==1&&digitalRead(sensorPin) == HIGH)
  {digitalWrite(D1,HIGH);
    delay(800);
    digitalWrite(D1,LOW);
    delay(200);   //the blinking indicates one second
    }
    if(flag==1&&digitalRead(sensorPin)==LOW)
   { stopTime = millis();
    elapsedTime = stopTime - startTime;
    Serial.println("stop time=");
    Serial.println(stopTime);
    Serial.println("ms");
    Serial.println();
    delay(500);
    Serial.println("Elapsed time=");
    Serial.println(elapsedTime);
    Serial.println("ms");
    Serial.println();
    delay(500);
    flag=0;
   } 
   
 if(elapsedTime>=3000)
 { 
  if (count<=2)
{Serial.print("connecting to ");
          Serial.println(host);
          WiFiClient client;
          const int httpPort = 80;
          if (!client.connect(host, httpPort)) 
          {
            Serial.println("connection failed");
            return;
          }
           String url = "/trigger/sensorTouched/with/key/bdDBujcGlLVdpDsRJmBanu";
          
          Serial.print("Requesting URL: ");
          Serial.println(url);
           client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
             delay(5000);
             count=count+1;
              digitalWrite(D1,HIGH);
              delay(200);
              digitalWrite(D1,LOW);
              delay(200);
              digitalWrite(D1,HIGH);
              delay(200);
              digitalWrite(D1,LOW);
              delay(200);   
 }
 if(count==3){digitalWrite(D1,HIGH);} //LED will be always on until reset

 }
}   
