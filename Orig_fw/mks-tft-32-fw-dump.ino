

// constants won't change. Used here to set a pin number:
const int ledPin =  PA5;// this is ext_sdcard connector 
const int signal_pin = PB0;//pulse that we are working somthing
const int final_pin = PB3;//this is clk on sd card

// Variables will change:
int ledState = LOW;             // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 1000;           // interval at which to blink (milliseconds)
#include <SPI.h>
#include <SD.h>

File root;

void testpatch(void)
{
 
WWDG->SR = 0;

TIM1->CR1=0;
TIM2->CR1=0;
TIM1->BDTR=0;
BKP->CR=0;

HAL_NVIC_DisableIRQ(TIM1_TRG_COM_IRQn);
HAL_NVIC_DisableIRQ(TIM1_CC_IRQn);
HAL_NVIC_DisableIRQ(TIM1_BRK_IRQn);
HAL_NVIC_DisableIRQ(TAMPER_IRQn);
HAL_NVIC_DisableIRQ(SPI3_IRQn);
HAL_NVIC_DisableIRQ(SPI2_IRQn);
HAL_NVIC_DisableIRQ(SPI1_IRQn);
//SCB->VTOR = (FLASH_BASE | 0x8000);
__HAL_DBGMCU_FREEZE_WWDG();
HAL_SuspendTick();
//HAL_RCC_DeInit();

}
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
static void MX_USART3_UART_Init(void)
{
    huart3.Instance = USART3;
    huart3.Init.BaudRate = 115200;
    huart3.Init.WordLength = UART_WORDLENGTH_8B;
    huart3.Init.StopBits = UART_STOPBITS_1;
    huart3.Init.Parity = UART_PARITY_NONE;
    huart3.Init.Mode = UART_MODE_TX_RX;
    huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart3.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart3) != HAL_OK)
        Error_Handler();
}
static void MX_USART2_UART_Init(void)
{
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart2) != HAL_OK)
        Error_Handler();
}

void setup() {
  // set the digital pin as output:
 // pinMode(ledPin, OUTPUT);
  pinMode(signal_pin ,OUTPUT);
  //pinMode(final_pin,OUTPUT);
 //while (1)
 //{
 //initVariant();
// }
//NVIC_SystemReset();
testpatch();
Serial1.begin(115200);
digitalWrite(ledPin,LOW);
HAL_Init();
SystemInit();
SystemClock_Config();


SystemCoreClockUpdate();
}

void save_flash(void)
{
 Serial.print("Initializing SD card...");

  if (!SD.begin(PIN_SPI_SS)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
}

void dump_flash(void)
{
  Serial1.println("FLASH START");
  Serial1.write(0x0);
  Serial1.write(0x0);
  Serial1.write(0x0);
  Serial1.write(0x0);
  Serial1.write(0xAA);
  Serial1.write(0x55);
  Serial1.write(0x0);
   for (uint32_t addr = 0x08000000; addr <= 0x08010000; addr++) {
        //usart_send_blocking(USART2, *((uint16_t *) addr));
        Serial1.write(*((uint16_t *) addr));
        
        delay(4);
    }

}
void loop() {

  
    // set the LED with the ledState of the variable:
   // digitalWrite(ledPin, !digitalRead(ledPin));
    digitalWrite(signal_pin, !digitalRead(signal_pin));
  //  digitalWrite(final_pin, !digitalRead(final_pin));
    Serial1.println("darkspr1te PWNED");
        dump_flash();
 // save_flash();
}
