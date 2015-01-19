#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"
#include "call.h"

SMSGSM sms;
CallGSM call;

boolean started=false;
boolean calling=false;

int buttonState = 0 ;
const int POWER_LED_PIN = 5;
const int BUTTON_LED_PIN = 6;
const int BUTTON1_PIN = 10;
const int BUTTON2_PIN = 11;
const int BUTTON3_PIN = 12;
const int BUTTON4_PIN = 13;

void setup()
{
  Serial.begin(9600);
  Serial.println("Staring...");
  pinMode(POWER_LED_PIN, OUTPUT);
  pinMode(BUTTON_LED_PIN, OUTPUT);
  pinMode(BUTTON1_PIN, INPUT);
  pinMode(BUTTON2_PIN, INPUT);
  pinMode(BUTTON3_PIN, INPUT);
  pinMode(BUTTON4_PIN, INPUT);
  if (gsm.begin(9600)) 
  {
    started=true;
    digitalWrite(POWER_LED_PIN,HIGH);
    Serial.println("Connected...");
  } 

  if(started) 
  {
    digitalWrite(POWER_LED_PIN,HIGH);
    digitalWrite(BUTTON_LED_PIN, HIGH);
    delay(2000);    
    digitalWrite(BUTTON_LED_PIN, LOW);
  }

};

void loop()
{
  if(started) 
  {
    buttonState = isButtonPressed();

    // check if the pushbutton is pressed.
    // if it is, the buttonState is HIGH:
    if (buttonState == HIGH) {     
      Serial.println("Pressed...");
      // turn LED on:    
      digitalWrite(BUTTON_LED_PIN, HIGH); 
      if(!calling){
        sendSmsHelp();
        Serial.println("Calling...");
        callHelp(); 
      }
    } 
    else {
      // turn LED off:
      digitalWrite(BUTTON_LED_PIN, LOW); 
    } 
    if(calling && call.CallStatus()==0){
      calling = false;
    }
  }
};

void callHelp(){
  
  calling=true;
  call.Call(1);
};

void sendSmsHelp(){
  char phone_num[20];
  for(int i=1;i<20;i++){
    if(1 == gsm.GetPhoneNumber(i,phone_num)){
      Serial.print("Sending sms to ");
      Serial.println(phone_num);
      sms.SendSMS(i,"Babcia w potrzebie!!");
    }
  }
}

int isButtonPressed(){
  if ((digitalRead(BUTTON1_PIN)==HIGH) || (digitalRead(BUTTON2_PIN)==HIGH) || (digitalRead(BUTTON3_PIN)==HIGH) || (digitalRead(BUTTON4_PIN)==HIGH)){
    return HIGH;
  }else{
    return LOW;
  }
}
