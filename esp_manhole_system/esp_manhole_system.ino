//node mcu esp8266
//MANASVI SINGH
#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
WiFiServer server(80);
#define BLYNK_TEMPLATE_ID "TMPL3wriRKJIz"   //Your Template Id
#define BLYNK_TEMPLATE_NAME "Manhole Detection and Monitoring System"  //Your Template name
#define BLYNK_AUTH_TOKEN "grbgIZ5KVFP3MxZuou1Pk9GI8bp7-DLS"  //Your auth token
char auth[] = BLYNK_AUTH_TOKEN;             // Authentication Token Sent by Blynk
char ssid[] = "coffee";        //WiFi SSID
char pass[] = "coffee19";        //WiFi Password
WidgetLED led(V0);              //widget LED defined at V0 (virtual pin 0) on blynk 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);        //deafult node MCU baud rate
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  Blynk.begin(auth, ssid, pass,"blr1.blynk.cloud");  //we write "blr1.blynk.cloud" to connect to the banglore server 
    while (WiFi.status() != WL_CONNECTED)// while wifi not connected
  {
    delay(500);
    Serial.print("."); //print "...."
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());  // Print the IP address
  
}

void loop() {
  Blynk.run();
  float mgswitch=0,ultrasonic=0,gassensor=0;
  // put your main code here, to run repeatedly:
  if(Serial.available()>0)
  {
   String data=Serial.readStringUntil('\n');  //Storing the string value that we recieve from arduino into data
   String a[]={" "," "," "};
   int i=0;int c=0;
    while (c<data.length()) {         //loop to split those values
      if(data.charAt(c)==','){
      i++;c++;
      }
        a[i]+=data.charAt(c);
        c++;
    }
    mgswitch=a[0].toFloat();
    ultrasonic=a[1].toFloat();
    gassensor=a[2].toFloat();
  }
  Serial.println(mgswitch);
  Serial.println(ultrasonic);
  Serial.println(gassensor);
  Blynk.virtualWrite(V1, ultrasonic);  //Sending distance value to blynk's virtual pin 1 (V1)
  Blynk.virtualWrite(V2, gassensor);  //Sending gas sensor value to blynk's virtual pin 1 (V1)
  if(mgswitch==0)
  led.off();
  else
  led.on();
  delay(500);//this delay is in miliseconds
}
