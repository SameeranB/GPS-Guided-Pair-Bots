#include<TinyGPS++.h>

TinyGPSPlus gps;
long double HilGPSlat=0, HilGPSlon=0;
long double flat,flon;
void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);

  

}

void loop() {

  
    GetGps();
  
}
void GetGps()
{
  
   bool newData = false;
  
  
  int i=1;char d;
   while(i<=10) 
   {
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
  while (Serial1.available())
    {
      char c = Serial1.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }
  

  if (newData)
  {
       
    flat=gps.location.lat();
    flon=gps.location.lng();


    } 
   
    
    
    HilGPSlat+=flat ;
    HilGPSlon+=flon ;
    i++;
    
}
Serial.print((double)HilGPSlat/10);
Serial.print("    ");
Serial.println((double)HilGPSlon/10);
HilGPSlat=0;
HilGPSlon=0;
   
}

