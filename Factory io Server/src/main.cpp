#include <Arduino.h>

#ifdef ESP8266
 #include <ESP8266WiFi.h>
#else //ESP32
 #include <WiFi.h>
#endif
#include <ModbusIP_ESP8266.h>
#define joystic_x 32
#define joystic_y 33
unsigned long previousMillis = 0;
const long interval = 100;
float temp=0;

int x_analog_val=0;
int y_analog_val=0;

bool latch;
//ModbusIP object
ModbusIP mb;

#define BUTTON_PIN 21  // GIOP21 pin connected to button
#define BUTTON1_PIN 22
#define BUTTON2_PIN 23


// Variables will change:
int lastState = LOW;  // the previous state from the input pin
int lastState1 = LOW;
int lastState2 = LOW;




int currentState;     // the current reading from the input pin
int currentState1;
int currentState2;


uint16_t z_axis=0;
uint16_t x_axis=0;
uint16_t y_axis=0;



void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLDOWN);
  
  WiFi.begin("Wifi Name", "Wifi_Pass");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");  
  }
  
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 
  mb.server();
  mb.addCoil(10,false);
  mb.addHreg(3,x_axis);
  mb.addHreg(4,y_axis);
  mb.addHreg(5,z_axis);
  /*Factory IO
I/O Config
------------
Read Digital 
:Coils

Read Register:
Holding Registers
  Offset:100
I/O Points

                    Ofset    Count
Digital  Inputs       0        2
Digital  Outputs      2        2




*/
 
 
}
 
void loop() {
    unsigned long currentMillis = millis();

   //Call once inside loop() - all magic here
   mb.task();
    x_analog_val=analogRead(joystic_x);
    y_analog_val=analogRead(joystic_y);
   if (currentMillis - previousMillis >= interval) {
    // Save the last time something happened
    

    if (x_analog_val>3028 && x_axis<=9)
   {
    x_axis++;
   }
   if (x_analog_val<1028 && x_axis>0)
   {
    x_axis--;
   }

    if (y_analog_val>3028 && y_axis<=9)
   {
    y_axis++;
   }
   if (y_analog_val<1028 && y_axis>0)
   {
    y_axis--;
   }


previousMillis = currentMillis;
   }
   



   currentState = digitalRead(BUTTON_PIN);
  if (lastState == HIGH && currentState == LOW){
    Serial.println("The button is pressed");
    if (z_axis<10)
    {
      z_axis++;
    }
    
    }
  else if(lastState == LOW && currentState == HIGH){
    Serial.println("The button is released");
  // save the the last state
   //mb.Hreg(5,z_axis);
  }
lastState = currentState;

currentState1 = digitalRead(BUTTON1_PIN);
  if (lastState1 == HIGH && currentState1 == LOW) {
    Serial.println("Button 1 is pressed");
    if (z_axis>0)
    {
      z_axis--;
    }
    
  } else if (lastState1 == LOW && currentState1 == HIGH) {
    Serial.println("Button 1 is released");
  }
  lastState1 = currentState1;

currentState2 = digitalRead(BUTTON2_PIN);
  if (lastState2 == LOW && currentState2 == HIGH) {
    Serial.println("Button 2 is pressed");
    switch (mb.Coil(10))
    {
    case true:
      mb.Coil(10,false);   
      break;
    case false:
   
      mb.Coil(10,true);
      break;
    
    default:
      break;
    }

  
  } else if (lastState2 == HIGH && currentState2 == LOW) {
    Serial.println("Button 2 is released");
  }
  lastState2 = currentState2;


     mb.Hreg(3,x_axis);
  mb.Hreg(4,y_axis);
  mb.Hreg(5,z_axis);

   delay(10);
}
