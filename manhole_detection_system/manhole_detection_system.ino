//arduino code
//MANASVI SINGH

//variables
long duration;
float distanceCm;
int sensorPin = A0;
bool state;
String doorState;
const int reedSwitch = 9;
const int buzzer=8;
bool changeState = false; //this variable is used to check if the 

//ultrasonic
#define ECHOPIN 7
#define TRIGPIN 6
#define SOUND_VELOCITY 0.034
//oled

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


void setup() {
  Serial.begin(115200);  //the default baud rate for Arduino uno is 9600 but all our devices should have the same baud rate to work so we specify the baud rate as 115200

  pinMode(A0, INPUT);

  pinMode(ECHOPIN,INPUT_PULLUP);
  pinMode(TRIGPIN, OUTPUT);
  digitalWrite(ECHOPIN, HIGH);
  pinMode(reedSwitch, INPUT_PULLUP);
  
  pinMode(8,OUTPUT);//buzzer
  digitalWrite(buzzer, LOW);
  
  state = digitalRead(reedSwitch);

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  delay(2000);         // wait for initializing
  oled.clearDisplay(); // clear display
}

void loop() {
//ultrasonic
   digitalWrite(TRIGPIN, LOW);
   delayMicroseconds(2);
   digitalWrite(TRIGPIN, HIGH);
   delayMicroseconds(10);
   digitalWrite(TRIGPIN, LOW);
   duration = pulseIn(ECHOPIN, HIGH);
   //magnetic switch
   state = digitalRead(reedSwitch);
    Serial.print(state);
    Serial.print(",");
    if(state==1 || state==true){
    digitalWrite(buzzer,HIGH);
    }
    else digitalWrite(buzzer,LOW);
    //gas sensor
    int val = analogRead(A0);

    distanceCm = duration * SOUND_VELOCITY/2;
    Serial.print(distanceCm);
    Serial.print(",");
    Serial.println(val);
    
    //OLED
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(1);
    oled.setCursor(0, 0);
    oled.print("Distance (cm): ");
    oled.println(distanceCm);
    oled.setCursor(0,16);
    oled.print("gas level: ");
    oled.println(val);
      if(state==1 || state==true)
      {
        oled.setCursor(0,32);
        oled.print(" LID OPEN! ");
        }
    oled.display();
    delay(500);
}