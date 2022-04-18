//poids
#include <HX711.h>

#include "HX711.h"

HX711 scale(A0, A1); //HX711 scale(SCK, DT);

float calibration_factor = -480;
float units;
float ounces;


#define pas 10
char data;
int x;

void setup() {
scale.set_scale(calibration_factor);
scale.tare();
Serial.begin(9600);

}

void loop() {
if(Serial.available())
{
  data=Serial.read();
  if(data=='1')
  {
    //Serial.print("Reading:");
    //Serial.write('1');
    //Serial.println();
    //delay(5000);
  units = scale.get_units(),10;
  if (units < 0)
  {
    units = 0.00;
  }
 // ounces = units * 0.035274;
  Serial.println(units);
  
  //Serial.println(" grams");
  //delay(2000);
  
  }
  
  else if(data=='0')
  {
     }
     
}

}
