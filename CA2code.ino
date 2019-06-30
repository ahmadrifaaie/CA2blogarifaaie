int analogPin=A0;//Potentiometer Pin
int ledPin=8;  //LEDPin
int trPin=11; //Transistor Pin
int val; //Value from Analog Pin
int angle; //angle for servo to turn

 
 void setup() {
   // set  the transistor pin as output:
   pinMode(trPin, OUTPUT);
   pinMode(ledPin, OUTPUT);
   pinMode(analogPin, INPUT);
   Serial.begin(9600);
 }
 
 void loop() {
   // read the potentiometer:
   int sensorValue = analogRead(A0);
   // map the sensor value to a range from 0 - 255:
   val = map(sensorValue, 0, 1023, 0, 80);
   Serial.println(val);
   // use that to control the transistor:
   analogWrite(trPin, val);
   if (val>40)
   digitalWrite(ledPin,HIGH);
   else
   digitalWrite(ledPin,LOW);

 }
