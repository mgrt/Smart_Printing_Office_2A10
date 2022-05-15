#include <HX711.h>



#define PIN_LEDR1 2
#define PIN_LEDR2 3
#define PIN_LEDD 12
#define PIN_LEDO1 5
#define PIN_LEDO2 6
#define PIN_LEDV1 7
#define PIN_LEDV2 8
#define PIN_CAPTEUR1 10
#define PIN_CAPTEUR2 9
#define calibration_factor 967

char data ;
long Vcapteur;
int nbfeuille, poidsFeuille=0;

HX711 scale;

void setup() 
{
  //poidsFeuille=5;
  nbfeuille=0;
  
 pinMode(PIN_LEDR1,OUTPUT);
 pinMode(PIN_LEDR2,OUTPUT);
 pinMode(PIN_LEDD,OUTPUT);
 pinMode(PIN_LEDO1,OUTPUT);
 pinMode(PIN_LEDO2,OUTPUT);
 pinMode(PIN_LEDV1,OUTPUT);
 pinMode(PIN_LEDV2,OUTPUT);

scale.begin(PIN_CAPTEUR1,PIN_CAPTEUR2,128);
scale.set_scale(calibration_factor);
scale.tare();



 digitalWrite(PIN_LEDR1,LOW);
 digitalWrite(PIN_LEDR2,LOW);
 digitalWrite(PIN_LEDD,LOW);
 digitalWrite(PIN_LEDO1,LOW);
 digitalWrite(PIN_LEDO2,LOW);
 digitalWrite(PIN_LEDV1,LOW);
 digitalWrite(PIN_LEDV2,LOW);

 Serial.begin(9600);

}

void loop() 
{ 
       
  data=Serial.read();  
    if(data=='0')
     {
        digitalWrite(PIN_LEDD,LOW); 
        digitalWrite(PIN_LEDR1,LOW); 
        digitalWrite(PIN_LEDR2,LOW); 
        digitalWrite(PIN_LEDV1,LOW); 
        digitalWrite(PIN_LEDV2,LOW); 
        digitalWrite(PIN_LEDO1,LOW); 
        digitalWrite(PIN_LEDO2,LOW); 
     } 
     if(data=='1')
     {
      while(data=='1')
    {
      if(Serial.read()=='2')
      poidsFeuille++;

    if(Serial.read()=='3')
      poidsFeuille=0;
      
      Vcapteur = scale.get_units();
            nbfeuille = Vcapteur / poidsFeuille;  

 if(Serial.read()=='4')
  Serial.print(nbfeuille);
  // Serial.print(poidsFeuille);



      //Serial.write(nbf);
     
      
digitalWrite(PIN_LEDD,HIGH);
      
      if(nbfeuille<5)
      {
        digitalWrite(PIN_LEDR1,HIGH);
        digitalWrite(PIN_LEDR2,LOW);
        digitalWrite(PIN_LEDO1,LOW);
        digitalWrite(PIN_LEDO2,LOW);
        digitalWrite(PIN_LEDV1,LOW);
        digitalWrite(PIN_LEDV2,LOW);
   
        
      }else if(nbfeuille<10)
        {
          digitalWrite(PIN_LEDR1,HIGH);
          digitalWrite(PIN_LEDR2,HIGH);
          digitalWrite(PIN_LEDO1,LOW);
          digitalWrite(PIN_LEDO2,LOW);
          digitalWrite(PIN_LEDV1,LOW);
          digitalWrite(PIN_LEDV2,LOW);
        }else if(nbfeuille<15)
          {
           digitalWrite(PIN_LEDR1,HIGH);
           digitalWrite(PIN_LEDR2,HIGH);
           digitalWrite(PIN_LEDO1,HIGH);
           digitalWrite(PIN_LEDO2,LOW);
           digitalWrite(PIN_LEDV1,LOW);
           digitalWrite(PIN_LEDV2,LOW);
          }else if(nbfeuille<18)
              {         
               digitalWrite(PIN_LEDR1,HIGH);
               digitalWrite(PIN_LEDR2,HIGH);
               digitalWrite(PIN_LEDO1,HIGH);
               digitalWrite(PIN_LEDO2,HIGH);  
               digitalWrite(PIN_LEDV1,LOW);
               digitalWrite(PIN_LEDV2,LOW); 
              }else if(nbfeuille<22)
                {
                 digitalWrite(PIN_LEDR1,HIGH);
                 digitalWrite(PIN_LEDR2,HIGH);
                 digitalWrite(PIN_LEDO1,HIGH);
                 digitalWrite(PIN_LEDO2,HIGH);  
                 digitalWrite(PIN_LEDV1,HIGH);
                 digitalWrite(PIN_LEDV2,LOW);  
                }else if(nbfeuille>22)
                  {
                 digitalWrite(PIN_LEDR1,HIGH);
                 digitalWrite(PIN_LEDR2,HIGH);
                 digitalWrite(PIN_LEDO1,HIGH);
                 digitalWrite(PIN_LEDO2,HIGH);  
                 digitalWrite(PIN_LEDV1,HIGH); 
                 digitalWrite(PIN_LEDV2,HIGH);                   
                  }
    
  if (Serial.read()=='0')
  {
      data='0';
   }

        
    }   
    
     }
  
}
