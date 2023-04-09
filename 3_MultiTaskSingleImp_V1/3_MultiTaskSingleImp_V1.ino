// Instead of creating 3 Task Impl, this is how we can pass different parameters to single task Imp, compiler will create 3 task Imp in this case.(verify)


#include <Arduino_FreeRTOS.h>

// #define YELLOW    6
// #define GREEN     7
// #define BLUE      8
// #define WHITE     4
// #define RED       5

// #define RED_BUTTON    2
// #define GREEN_BUTTON  3

typedef struct{
  uint8_t led;
  uint16_t delay;
} LedStruct_t;


#define SET(digitalPin) digitalWrite(digitalPin, HIGH)
#define RESET(digitalPin) digitalWrite(digitalPin, LOW)
#define TOGGLE(digitalPin) digitalWrite(digitalPin, digitalRead(digitalPin)^1)



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  LedStruct_t led_yellow  = {6, 200};
  LedStruct_t led_green   = {7, 300};
  // LedStruct_t led_blue    = {8, 400};
  // LedStruct_t led_white   = {4, 500};
  // LedStruct_t led_red     = {5, 600};

  xTaskCreate(ledControllerTask, "YellowLED",128,(void *)&led_yellow,1,NULL);
  xTaskCreate(ledControllerTask, "greenLED",128,(void *)&led_green,1,NULL);
  // xTaskCreate(ledControllerTask, "blueLED",128,&led_blue,1,NULL);
  // xTaskCreate(ledControllerTask, "whiteLED",128,&led_white,1,NULL);
  // xTaskCreate(ledControllerTask, "redLED",128,&led_red,1,NULL);
}
void ledControllerTask(void *pvParameters){

  LedStruct_t *ledStructPtr = (LedStruct_t *)pvParameters;

  pinMode(ledStructPtr->led, OUTPUT);
  while(1){
    TOGGLE(ledStructPtr->led);
    vTaskDelay(ledStructPtr->delay/ portTICK_PERIOD_MS);     
  }
}
void loop() {
}
