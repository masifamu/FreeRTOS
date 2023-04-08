#include <Arduino_FreeRTOS.h>

#define YELLOW 7
#define GREEN  6
#define BLUE   8

typedef int taskProfiler;
taskProfiler yellowLedProfiler = 0;
taskProfiler greenLedProfiler = 0;
taskProfiler blueLedProfiler = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  xTaskCreate(yellowLedControllerTask, "YellowLED",128,NULL,1,NULL);
  xTaskCreate(greenLedControllerTask, "greenLED",128,NULL,1,NULL);
  xTaskCreate(blueLedControllerTask, "blueLED",128,NULL,1,NULL);
}
void yellowLedControllerTask(void *pvParameters){
  pinMode(YELLOW, OUTPUT);
  while(1){
    yellowLedProfiler++;
    Serial.print("YellowLedProfiler: ");Serial.println(yellowLedProfiler);
    digitalWrite(YELLOW, digitalRead(YELLOW)^1); 
    delay(300);     
  }
}
void greenLedControllerTask(void *pvParameters){
  pinMode(GREEN, OUTPUT);
  while(1){
    greenLedProfiler++;
    Serial.print("greenLedProfiler: ");Serial.println(greenLedProfiler);
    digitalWrite(GREEN, digitalRead(GREEN)^1);
    delay(300);
  }
}
void blueLedControllerTask(void *pvParameters){
  pinMode(BLUE, OUTPUT);
  while(1){
    blueLedProfiler++;
    Serial.print("blueLedProfiler: ");Serial.println(blueLedProfiler);
    digitalWrite(BLUE, digitalRead(BLUE)^1);
    delay(300);
  }
}
void loop() {
}
