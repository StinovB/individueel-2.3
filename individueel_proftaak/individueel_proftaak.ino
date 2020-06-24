#include <OneWire.h>
#include <MQ2.h> 
#include <DallasTemperature.h>
#include <Keypad.h> 

/** auteur Stijn van Berkel
 *  01/04/2020
 */
 //rgb colors
int red_light_pin= 13;
int green_light_pin = 12;
int blue_light_pin = 11;

//passcode for keypad
String code = "2468";

const byte numRows = 4;
const byte numCols = 3;

char keymap[numRows][numCols]= 
      {
      {'1', '2', '3'},
      {'4', '5', '6'},
      {'7', '8', '9'},
      {'*', '0', '#'},
      };

byte rowPins[numRows] = {10, 9, 8, 7};
byte colPins[numCols] = {6,5,4};

Keypad keypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

//I2C pins declaration
int Analog_Input = A0;
long smoke;

MQ2 mq2(Analog_Input);

void setup()
{  
  Serial.begin(9600);
  mq2.begin();
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
}

void loop()
{  
  float* values= mq2.read(true);
  smoke = mq2.readSmoke(); //if smoke is detected it goes up from 1-3
   
  if(smoke >= 1.0)
  {
    smokeDetected();
  }
  else
  {
    RGB_color(255, 255, 255); // White
  }
}

//changes led to given value.
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
{
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}

void smokeDetected()
{
  bool isGuessed = false;
  while(1)
  {
    char keypressed = keypad.getKey();
    if(keypressed == '*')
    {
      Serial.println("* PRESSED");
      isGuessed = Getpassword();
    }
    if(isGuessed){
      RGB_color(0, 255, 0);
      Serial.println("alarm stopped");
      return;
    }
    else
    { 
    Serial.println("SmokeDetected");
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
  }
}

bool Getpassword()
{
  RGB_color(255, 0, 0);
  while(1)
   {
     String userCombination;
     userCombination = getCombination();
     if(userCombination == code){
      Serial.println("Code Correct");
      return true;
     } 
     else
     {
      Serial.println("wrong code");
      return false;
     }
   }
}

String getCombination()
{
  int passwordIndex = 0;
  String guessedPassword = "";

  while(passwordIndex < 4)
  {
    char keyPressed = keypad.waitForKey();

    guessedPassword += keyPressed;
    passwordIndex++;
    delay(125);
  }
  
  return guessedPassword;
}
