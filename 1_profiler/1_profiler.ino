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
    SET(YELLOW);
    yellowLedProfiler++;
    Serial.print("YellowLedProfiler: ");Serial.println(yellowLedProfiler);
    RESET(YELLOW);
    delay(300);     
  }
}
void greenLedControllerTask(void *pvParameters){
  pinMode(GREEN, OUTPUT);
  while(1){
    SET(GREEN);
    greenLedProfiler++;
    Serial.print("greenLedProfiler: ");Serial.println(greenLedProfiler);
    RESET(GREEN);
    delay(300);
  }
}
void blueLedControllerTask(void *pvParameters){
  pinMode(BLUE, OUTPUT);
  while(1){
    SET(BLUE);
    blueLedProfiler++;
    Serial.print("blueLedProfiler: ");Serial.println(blueLedProfiler);
    RESET(BLUE);
    delay(300);
  }
}
void loop() {
}
