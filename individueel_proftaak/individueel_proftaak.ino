#include <OneWire.h>
#include <MQ2.h> 
#include <DallasTemperature.h> 

/** auteur Stijn van Berkel
 *  01/04/2020
 */
int red_light_pin= 11;
int green_light_pin = 10;
int blue_light_pin = 9;


//I2C pins declaration
int Analog_Input = A0;
long smoke;

MQ2 mq2(Analog_Input);

void setup(){
  Serial.begin(9600);
  mq2.begin();
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
}
void loop(){
  float* values= mq2.read(true);
  smoke = mq2.readSmoke(); //if smoke is detected it goes up from 1-3
//
  Serial.print("sMOKE");
  Serial.print(smoke);
  Serial.println();
  if(smoke >= 1.0){
    smokeDetected();
  }else{
    RGB_color(255, 255, 255); // White
  }
  
}

//changes led to given value.
void RGB_color(int red_light_value, int green_light_value, int blue_light_value){
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}

void smokeDetected(){

    RGB_color(255, 0, 0); // Red
    delay(100);
    RGB_color(0, 255, 0); // Green
    delay(100);
    RGB_color(0, 0, 255); // Blue
    delay(100);
    RGB_color(255, 255, 125); // Raspberry
    delay(100);
    RGB_color(0, 255, 255); // Cyan
    delay(100);
    RGB_color(255, 0, 255); // Magenta
    delay(100);
    RGB_color(255, 255, 0); // Yellow
    delay(100); 
}
