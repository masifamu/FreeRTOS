// Instead of creating 3 Task Impl, this is how we can pass different parameters to single task Imp, compiler will create 3 task Imp in this case.


#include <Arduino_FreeRTOS.h>

#define YELLOW    6
#define GREEN     7
#define BLUE      8
#define WHITE     4
#define RED       5

#define RED_BUTTON    2
#define GREEN_BUTTON  3


#define SET(digitalPin) digitalWrite(digitalPin, HIGH)
#define RESET(digitalPin) digitalWrite(digitalPin, LOW)
#define TOGGLE(digitalPin) digitalWrite(digitalPin, digitalRead(digitalPin)^1)



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  xTaskCreate(ledControllerTask, "YellowLED",128,(void *)((uint16_t *)YELLOW),1,NULL);
  xTaskCreate(ledControllerTask, "greenLED",128,(void *)((uint16_t *)GREEN),1,NULL);
  xTaskCreate(ledControllerTask, "blueLED",128,(void *)((uint16_t *)BLUE),1,NULL);
}
void ledControllerTask(void *pvParameters){
  pinMode(pvParameters, OUTPUT);
  while(1){
    TOGGLE(pvParameters);
    delay(300);     
  }
}
void loop() {
}
