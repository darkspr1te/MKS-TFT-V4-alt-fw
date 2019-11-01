#include <UTFT.h>

extern uint8_t SmallFont[];


#define WITCH 400


//UTFT lcdthingyname(byte model, int RS, int WR, int CS, int RST, int SER)
UTFT myGLCD(HX8353C,LCD_RS,LCD_WR,LCD_CS,0);
//UTFT myGLCD(0,LCD_RS,LCD_WR,LCD_CS,0);
#define LED LED_BUILTIN


void setup()
{
  randomSeed(analogRead(0));
// Setup the LCD
  myGLCD.Init();
  myGLCD.lcdOn();
  myGLCD.setFont(SmallFont);
  myGLCD.clrScr();
  
  pinMode(PD14,OUTPUT); 
  digitalWrite(PD14,HIGH);
  //Serial1.begin(115200);
  Serial.begin(115200);
  Serial.print("testing ");
  Serial.println(analogRead(0));
  delay(100);
   Serial.println(analogRead(0));
}
int counter =0;
void test_text()
{
  myGLCD.clrScr();

  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRect(0, 0, WITCH-1, 13);
  myGLCD.setColor(64, 64, 64);
  myGLCD.fillRect(0, 226, WITCH-1, 320);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.printStr("* STM32 Color TFT Display Library *", CENTER, 1);
  myGLCD.setBackColor(64, 64, 64);
  myGLCD.setColor(255,255,0);
  myGLCD.printStr("<darkspr1te>", CENTER, 227);

  myGLCD.setColor(0, 0, 255);
  myGLCD.drawRect(0, 14, WITCH-1, 225);
  Serial.print("testing serial port ");
  Serial.println(analogRead(0));
  delay(100);
   Serial.println(analogRead(0));
   Serial.println(counter);
}

void loop()
{
  delay(1000);
  test_text();
  counter++;
  delay(1000);
}
