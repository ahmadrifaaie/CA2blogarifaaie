
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include<stdint.h>
#include <Servo.h>
Servo myservo; 
int getFingerprintIDez();
int pos = 180;  
byte greenLed=12;
byte redLed=13;

// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (YELLOW wire)

SoftwareSerial mySerial(2, 3);  //activates serial communication on pin 2 & 3

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup() {
  pinMode(greenLed,OUTPUT);
  pinMode(redLed,OUTPUT);
  digitalWrite(redLed,LOW);
  myservo.attach(11);
  myservo.write(pos);
  Serial.begin(9600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");
  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger...");
}

void loop()                     // run over and over again
          {
            getFingerprintID();      
            delay(100);
          
          }

uint8_t getFingerprintID() 
{
  uint8_t p = finger.getImage();
 
  switch (p) 
        {
          case FINGERPRINT_OK:
             break;
          case FINGERPRINT_NOFINGER: 
            return p;
          case FINGERPRINT_PACKETRECIEVEERR:
            return p;
          case FINGERPRINT_IMAGEFAIL:
            return p;
          default:
            return p;
        }

  // OK success!
  p = finger.image2Tz();
  switch (p) 
      {
          case FINGERPRINT_OK:
            break;
          case FINGERPRINT_IMAGEMESS:
             return p;
          case FINGERPRINT_PACKETRECIEVEERR:
            return p;
          case FINGERPRINT_FEATUREFAIL:
            return p;
          case FINGERPRINT_INVALIDIMAGE:
            return p;
            default:
            return p;
      }
  
  // OK converted!
  p = finger.fingerFastSearch();
      if (p == FINGERPRINT_OK)
      {  
           myservo.write(0);
         digitalWrite(greenLed, HIGH);  
         digitalWrite(redLed,LOW);//turn on LED if finger ID is match
        } 
      else if(p == FINGERPRINT_NOTFOUND) 
        {
          digitalWrite(greenLed, LOW); 
          digitalWrite(redLed,HIGH);//turn off LED if finger do not match
          return p;
        }
      else
        {    return p;   }
 Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
  

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
                    uint8_t p = finger.getImage();
                        if (p != FINGERPRINT_OK)  return -1;
                      
                        p = finger.image2Tz();
                        if (p != FINGERPRINT_OK)  return -1;
                      
                        p = finger.fingerFastSearch();
                        if (p != FINGERPRINT_OK)  return -1;

}
