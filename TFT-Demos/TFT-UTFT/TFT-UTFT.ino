#include "UTFT.h"
#include "memorysaver.h"
#include <SPI.h>
#include <SD.h>
#include <XPT2046_Touchscreen.h>


UTFT myGLCD(HX8353C,LCD_RS,LCD_WR,LCD_CS,LCD_RD,LANDSCAPE);
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
  GPIO_InitTypeDef GPIO_InitStruct;
#define FW_VERSION "1  darkspr1te"
TS_Point p;
XPT2046_Touchscreen ts(TOUCH_CS);
#define X_RES 320
#define Y_RES 240
#define pin LCD_LED
#define dlay  8
#define freq 60
#define gamma_start 45

void Update_IT_callback(HardwareTimer*)
{ // Update event correspond to Rising edge of PWM when configured in PWM1 mod
//  digitalWrite(pin2, HIGH); // pin2 will be complementary to pin
}

void Compare_IT_callback(HardwareTimer*)
{ // Compare match event correspond to falling edge of PWM when configured in PWM1 mode
//  digitalWrite(pin2, LOW);
}
TIM_TypeDef *Instance = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(pin), PinMap_PWM);
uint32_t channel = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(pin), PinMap_PWM));
HardwareTimer *MyTim = new HardwareTimer(Instance);

void change_pwm(int x,int y)
{
  MyTim->setPWM(channel, pin,x, y); 
}
void config_pwm()
{
   MyTim->setPWM(channel, pin,1000, 60); 
   MyTim->attachInterrupt(Update_IT_callback);
   MyTim->attachInterrupt(channel, Compare_IT_callback);
   MyTim->resume();
}

void calibrationPoint(uint16_t calX, uint16_t calY,int colour) 
{
  myGLCD.setColor(colour);
  myGLCD.drawCircle(calX, calY, 20);
  myGLCD.drawHLine(calX-10, calY, 20);
  myGLCD.drawVLine(calX, calY-10, 20);
 
}
#define REGS(x) x
#define GROUP_MODE(port, reg, mask, val)  {port->REGS(reg) = (port->REGS(reg) & ~(mask)) | ((mask)&(val)); }
#define GP_OUT(port, reg, mask)           GROUP_MODE(port, reg, mask, 0x33333333)
#define GP_INP(port, reg, mask)           GROUP_MODE(port, reg, mask, 0x44444444)


uint16_t calA[] = {40, 50};  
uint16_t calB[] = {40, 50};  
uint16_t calC[] = {40, 50};  


void setup() {
   // first thing is spit out operational message
   Serial.begin(115200);
  Serial.println();
  Serial.print("Start MKS TFT System v1.");
  Serial.println(FW_VERSION);
  //pinMode(pin2,OUTPUT);
  //configure pins , ensure backlight off until setup
 
 // config_pwm();

 // pinMode(LCD_BACKLIGHT_PIN,OUTPUT); 
 // digitalWrite(LCD_BACKLIGHT_PIN,LOW);
  pinMode(LCD_RS,OUTPUT);
  pinMode(LCD_WR,OUTPUT);
  pinMode(SDCARD_CS,OUTPUT);
  pinMode(LCD_CS,OUTPUT);
  pinMode(LCD_RD,OUTPUT);
  pinMode(TOUCH_DI,INPUT);
  pinMode(TOUCH_CS,OUTPUT);
  //pinMode(TOUCH_CS,HIGH);
  //configure touch screen and LCD
  ts.begin();
  ts.setRotation(4);
  //void XPT2046_Touchscreen::calibrate(float ax, float bx, int16_t dx, float ay, float by, int16_t dy, uint16_t dwidth, uint16_t dheight, uint8_t drot)
 // ts.calibrate(0.0881,0.00355,0,0.07246,0.354,0,320,240,3);
 //ts.calibrate(0,0,0,0,0,0,320,240);
  myGLCD.Init(PORTRAIT);
  myGLCD.setFont(SmallFont);
  myGLCD.setColor(LIME);

  myGLCD.setBackColor(BLACK);
  //small delay then activate backlight
  delay(50);
  //digitalWrite(LCD_BACKLIGHT_PIN,HIGH);
  light_up();
  myGLCD.fillScr(BLACK);
  

  if (!ts.touched())
    myGLCD.fillScr(BLACK);
   else
   myGLCD.fillScr(RED);
   
  myGLCD.printStr("test mkstft", 1, 1,0);
  myGLCD.printStr("FW V", 1, 20,0);
  myGLCD.printStr(FW_VERSION, 65, 20,0);
 
  delay(500);
config_pwm();

}

String  get_regs(int regs, int reads)
{
  String we_return="";
  myGLCD.h_write_COM(regs);
  int data = myGLCD.h_read_DATA();//first two bytes dummy
  we_return = we_return+String((data&0xff),HEX);
   for (int xr=0;xr<reads;xr++)
  {
   data = myGLCD.h_read_DATA();
  we_return = we_return+String(data,HEX); 
  }
  return we_return;
}
byte reg_read[10];
void light_down()
{
  for (int gamma=gamma_start;gamma>0;gamma--)
  {
    change_pwm(freq,gamma);
    if (gamma<0)return;
    delay(dlay);
    Serial.print("Gamma ");
    Serial.println(gamma);
  }
  delay(200);
}
void light_up()
{
  for (int gamma=1;gamma<gamma_start;gamma++)
  {
    change_pwm(freq,gamma);
    if (gamma<0)return;
    delay(dlay);
    Serial.print("Gamma ");
    Serial.println(gamma);
  }
  
}
void print_regs_lcd()
{

 String thisstring;
  myGLCD.setFont(SmallFont);

  
  myGLCD.fillScr(BLACK);
  myGLCD.printStr("lcd man/mdl:", 1, 1,0);myGLCD.printStr(get_regs(0x04,2),95, 1,0);

  myGLCD.printStr("Reg 0x09",1,15,0);
  myGLCD.printStr("Reg 0x0A",1,25,0);
  myGLCD.printStr("Reg 0x0B",1,35,0);
  myGLCD.printStr("Reg 0x0C",1,45,0);
  myGLCD.printStr("Reg 0x0D",1,55,0);
  myGLCD.printStr("Reg 0x0E",1,65,0);
  myGLCD.printStr("Reg 0x0F",1,75,0);


  myGLCD.printStr(get_regs(0x09,2),75, 15,0);
  myGLCD.printStr(get_regs(0x0A,2),75, 25,0);
  myGLCD.printStr(get_regs(0x0B,2),75, 35,0);
  myGLCD.printStr(get_regs(0x0C,2),75, 45,0);
  myGLCD.printStr(get_regs(0x0D,2),75, 55,0);
  myGLCD.printStr(get_regs(0x0E,2),75, 65,0);
  myGLCD.printStr(get_regs(0x0F,1),75, 75,0);
  

   
}

void print_regs(int regs,int reads)
{
  myGLCD.h_write_COM(regs);
  Serial.print("Reg: 0x");
  Serial.print(regs,HEX);
  Serial.print(" ");
  for (int xr=0;xr<reads;xr++)
  {
  int data = myGLCD.h_read_DATA();
  Serial.print(data,HEX);
  if (xr==(reads-1)){}
  else
    Serial.print(",");
  }
  Serial.println();
}

int ylayer=0;
void do_regs()
{
   //Automated read lcd id
  Serial.print("LCD ID:");
  Serial.println(myGLCD.readID(),HEX);
  Serial.println("Reading registers:-");
  Serial.println();
  //Manual way 
  print_regs(0x04,4);//print lcd ID
  print_regs(0x09,4);//Read Display Status 4 words(reads)
  //print_regs(0x09,4);//Read Display Status 4 words(reads)
  Serial.print("Register 0x4 {ID} as a string :0x");
  Serial.println(get_regs(0x04,2));
  print_regs(0x0a,1);//Read Display power mode
  print_regs(0x0b,1);//Read Display  MADCTL
  print_regs(0x0c,1);//Read Display Pixel format
  print_regs(0x0d,1);//Read Display Image Mode
  print_regs(0x0e,1);//Read Display Signal Mode 
  print_regs(0x0f,1);//Read Display Self Diag result 
  print_regs(0xd0,4);//Read Display Self Diag result 
}
uint16_t color565(uint8_t r, uint8_t g, uint8_t b) {
  uint16_t rb, gb, bb;
  rb = (r & 0xF8) << 8;
  gb = (g & 0xFC) << 3;
  bb = b >> 3;
  return rb | gb | bb;
}
uint16_t readPixel(int16_t x, int16_t y) {
  uint8_t r, g, b;
  myGLCD.setXY(x, y, x, y);
  myGLCD.h_write_COM(0x2E);

  r = myGLCD.h_read_DATA();  //dummy
  r = myGLCD.h_read_DATA();
  g = myGLCD.h_read_DATA();
  b = myGLCD.h_read_DATA();
  return color565(r, g, b);//.kbv
}

int16_t  readGRAM(int16_t x, int16_t y, uint16_t *block, int16_t w, int16_t h)
{
  uint16_t *p;
  for (int row = 0; row < h; row++) {
    p = block + row * w;
    for (int col = 0; col < w; col++) {
    *p++ = readPixel(x + col, y + row);
    }
  }
}

void vertScroll(int16_t top, int16_t scrollines, int16_t offset)
{
  // .kbv add this line to Adafruit_ILI9341: friend class GLUEAdafruit_ILI9341;
  int16_t vsp = top + offset;  // vertical start position
  if (offset < 0)
  vsp += scrollines;  //keep in unsigned range
  int16_t bfa = Y_RES - top - scrollines;
  myGLCD.h_write_COM(0x0033);
  myGLCD.h_write_DATA(top >> 8);   //TOP
  myGLCD.h_write_DATA(top); //TOP
  myGLCD.h_write_DATA(scrollines >> 8);
  myGLCD.h_write_DATA(scrollines);
  myGLCD.h_write_DATA(bfa >> 8);
  myGLCD.h_write_DATA(bfa);
  myGLCD.h_write_COM(0x0037);
  myGLCD.h_write_DATA(vsp >> 8); //VL#
  myGLCD.h_write_DATA(vsp);   //VL#
}

void loop() {

  // put your main code here, to run repeatedly:
  delay(100);
 
light_up();
  do_regs();
print_regs_lcd();
delay(1000);
  calibrationPoint(150, 150,RED);

  ylayer++;
  if (ylayer>240){ylayer=0;}
  delay(100);
  //void vertScroll(int16_t top, int16_t scrollines, int16_t offset)
  vertScroll(20,20,50);
   delay(1000);
   light_down();
//  calibrationPoint(calC[0], calC[1],BLUE);
  //test_up();
}

 
