#include <Arduino_FreeRTOS.h>

#define YELLOW 7
#define GREEN  6
#define BLUE   8

void setup() {
  // put your setup code here, to run once:
  xTaskCreate(yellowLedControllerTask, "YellowLED",128,NULL,1,NULL);
  xTaskCreate(greenLedControllerTask, "greenLED",128,NULL,1,NULL);
  xTaskCreate(blueLedControllerTask, "blueLED",128,NULL,1,NULL);
}
void yellowLedControllerTask(void *pvParameters){
  pinMode(YELLOW, OUTPUT);
  while(1){
    digitalWrite(YELLOW, digitalRead(YELLOW)^1);      
  }
}
void greenLedControllerTask(void *pvParameters){
  pinMode(GREEN, OUTPUT);
  while(1){
    digitalWrite(GREEN, digitalRead(GREEN)^1);
  }
}
void blueLedControllerTask(void *pvParameters){
  pinMode(BLUE, OUTPUT);
  while(1){
    digitalWrite(BLUE, digitalRead(BLUE)^1);
  }
}
void loop() {
}
