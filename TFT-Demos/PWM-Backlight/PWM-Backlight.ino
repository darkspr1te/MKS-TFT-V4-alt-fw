/*
 * Demo of PWM control on the MKS-TFT V4 hardware
 * Pin PD14 is LCD backlight and PB0 is on Header for Filiment , PB0/FILIMENT is Pulsed in the same way as PD14 for scope hook up or testing
 * darkspr1te
 */

#define pin2 FILIMENT
#define pin LCD_LED
#define dlay  8
#define freq 60
#define gamma_start 45

void Update_IT_callback(HardwareTimer*)
{ // Update event correspond to Rising edge of PWM when configured in PWM1 mod
  digitalWrite(pin2, HIGH); // pin2 will be complementary to pin
}

void Compare_IT_callback(HardwareTimer*)
{ // Compare match event correspond to falling edge of PWM when configured in PWM1 mode
  digitalWrite(pin2, LOW);
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
void setup() {
   Serial.begin(115200);
   Serial.println();
   Serial.println("==========================");
   Serial.println("PWM-Backlight control Demo");
   Serial.println("==========================");

  pinMode(pin2,OUTPUT);
  config_pwm();
  // put your setup code here, to run once:

}

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
void loop() {
  // put your main code here, to run repeatedly:
light_down();
light_up();
}
