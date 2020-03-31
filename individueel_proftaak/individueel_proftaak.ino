#include <OneWire.h>
#include <DallasTemperature.h> 

float temp = 0.0;
int oneWireBus = 12;
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);


void setup() {
    Serial.begin(9600);
    Serial.println("Stijn van Berkel indidueel");
    sensors.begin();
   
}

void loop() {
    sensors.requestTemperatures();
    temp = sensors.getTempCByIndex(0);
    Serial.print("temperature is: ");
    Serial.println(temp);
    delay(1000);
}
