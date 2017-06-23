#include <SoftwareSerial.h>

int buzzPin = 8;
int inputPin = 4;
int pirState = LOW;
int val = 0;

int blueTx = 2;
int blueRx = 3;
SoftwareSerial mySerial(blueTx, blueRx);
String myString = "";

void setup()   {
   Serial.begin(9600);
   mySerial.begin(9600);
   pinMode(buzzPin, OUTPUT);
   pinMode(inputPin, INPUT);
}

void loop()   {
   while(mySerial.available())   {
      char myChar = (char)mySerial.read();
      myString += myChar;
      delay(5);
   }

   if(!myString.equals(""))   {
      Serial.println("input value: " + myString);
   
      if(myString =="on")   {
             val = digitalRead(inputPin); // 센서값 읽기
             if (val == HIGH) { // 인체감지시
               tone(buzzPin,500,3000); //버저 울림
               if (pirState == LOW) {
               // 시리얼모니터에 메시지 출력
               Serial.println("Motion detected!");
               pirState = HIGH;
               }
             } else {
               noTone(buzzPin); //버저 끔
               if (pirState == HIGH){        
                  // 시리얼모니터에 메시지 출력            
                   Serial.println("Motion ended!");
                   pirState = LOW;
               }
             }
      }
      else if(myString == "onoff") {
         noTone(buzzPin);
         myString = "";
      }
      else {
         noTone(buzzPin);
      }
    }
}
