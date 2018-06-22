#include <SPI.h>
#include "RF24.h"


RF24 radio(44,45);


byte addresses[][6] = {"1Node","2Node"};

  float Dul[2];
  float Cen[2];
  float DulGPSlat = 18.655;
  float DulGPSlon = 72.333;

  float cenlat, cenlon;








void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

  Dul[0]=DulGPSlat;
  Dul[1]=DulGPSlon;
  
 radio.begin();
 radio.setPALevel(RF24_PA_LOW);
 radio.setChannel(124); 
radio.openWritingPipe(addresses[1]);
radio.openReadingPipe(1,addresses[0]); 
  radio.stopListening();
}

void loop() {
  // Sending Coordinates
  char ch;
while (ch!='c')
{
  radio.stopListening();
  radio.write(&Dul, sizeof(float[2]));
  Serial.println("Coordinates Sent");
  radio.startListening();
    radio.read(&ch, sizeof(char));
   
  

delay(1000);
}

radio.startListening();
// Receiving Centre

char ch1='c';
Cen[0]=0.00;
while(Cen[0]==0.00)
{
if(radio.available())
{
  radio.read(&Cen, sizeof(float[2]));
}

}

radio.stopListening();

delay(5000);

Serial.println("Centre Coordinates - ");
Serial.print(Cen[0]);
Serial.print("     ");
Serial.println(Cen[1]);




}

