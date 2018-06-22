#include <SPI.h>
#include "RF24.h"



RF24 radio(44,45);


byte addresses[][6] = {"1Node","2Node"};

  float Dul[2];
  float Cen[2];
  float DulGPSlat;
  float DulGPSlon;

  float cenlat= 5.0505, cenlon= 5.0505;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

Cen[0]=cenlat;
Cen[1]=cenlon;


 radio.begin();
 radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(124);
 radio.openReadingPipe(1,addresses[1]); 
 radio.openWritingPipe(addresses[0]); 
  radio.startListening();

  
}

void loop() {
  // Receive Dul
      Dul[0]=0.00;
      char ch= 'c';
while(Dul[0]==0.00)
{
    if(radio.available())
   {
    radio.read(&Dul, sizeof(float[2]));
   }
   
  
   

    delay(1000);
    
}
radio.stopListening();
   radio.write(&ch, sizeof(char));
radio.stopListening();


    // Transmit Centre


unsigned long tm;
tm= millis();
while(millis()-tm < 1000)
{
  
    radio.stopListening();

   radio.write(&Cen, sizeof(float[2]));

 
   
}  Serial.println("Sent Succesfully");
   
   
 
  
   
  

delay(5000);
 Serial.println("Received - ");
   Serial.print(Dul[0]);
   Serial.print("   ");
   Serial.println(Dul[1]);
     

}
