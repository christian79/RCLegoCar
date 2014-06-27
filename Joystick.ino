
#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);
int valX;
int valX1;
int valY;
byte analogPinX = 0;
byte analogPinY = 1;
int cm = 0;
long previousMillis = 0;
long interval = 150;
long previousRXTXMillis = 0;
long RXTXinterval = 20;



void setup()
  {
    lcd.begin(16, 2);
    lcd.clear();
    Serial.begin(19200);
  // put your setup code here, to run once:

}

byte getDistance()
{
  cm = Serial.parseInt();
  if (cm < 50 )
  {
    return cm;
  }
}
void printForward()
{
  valX = constrain(valX, 3, 255);
  valY = constrain(valY, 0, 179);
  Serial.print("f");
  Serial.print(",");
  Serial.println(valX);
  Serial.print(",");
  Serial.println(valY);
  lcd.setCursor(0,1);
  lcd.print("f");
  lcd.print(",");
  lcd.print(valX);
  lcd.print(",");
  lcd.print(valY);
  //delay(20);
}

void printBackward()
{
  valX1 = constrain(valX1, 3, 255);
  valY = constrain(valY, 0, 179);
  Serial.print("b");
  Serial.print(",");
  Serial.println(valX1);
  Serial.print(",");
  Serial.println(valY);
  lcd.setCursor(0,1);
  lcd.print("b");
  lcd.print(",");
  lcd.print(valX1);
  lcd.print(",");
  lcd.print(valY);
  //delay(20);
}

void printStop()
{
  valY = constrain(valY, 0, 179);
  Serial.println("s");
  Serial.println(valY);
  lcd.setCursor(0, 1);
  lcd.print("s");
  lcd.print(",");
  lcd.print(valY);
  //delay(20);
}

void  LCDrefresh()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > interval)
    {
      previousMillis = currentMillis;
      lcd.clear();
    }
}
    
  
  
void loop()
  {
    valX = map(analogRead(analogPinX), 530, 1023, 0, 255);
    valX1 = map(analogRead(analogPinX), 516, 0, 0, 255);
    valY = map(analogRead(analogPinY), 0 ,1023, 0, 179);
    unsigned long currentRXTXMillis = millis();
  
  if (currentRXTXMillis - previousRXTXMillis > RXTXinterval)
  {
    previousRXTXMillis = currentRXTXMillis;
    if (valX > 3)
    {
      printForward();
    }
    if (valX < -4 )
    {
      printBackward();
    }
    else if ((valX < 3) && (valX > -4))
    {
      printStop();
    }
  }
    
  lcd.setCursor(0, 0);
  lcd.print("Distance cm: ");
  lcd.print(getDistance());  
  LCDrefresh();
}
