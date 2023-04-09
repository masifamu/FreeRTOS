/**
 * if configUSE_PREEMPTION is 1 then preemptive task scheduling is done by the scheduler and cooperative scheduling when it is 0.
 * However, i have tested configUSE_PREEMPTION as 0 and changed the priority of blueLED task as 2 then blue callback function is running only, even though
 * cooperative scheduling is activated priority is being considered by the schedular.
*/



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

//you can add profiler to check the task working as well

TaskHandle_t yellowTaskHandle;
TaskHandle_t greenTaskHandle;
TaskHandle_t blueTaskHandle;
TaskHandle_t whiteTaskHandle;
TaskHandle_t redTaskHandle;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  xTaskCreate(yellowLedControllerTask, "YellowLED",100,NULL,1,&yellowTaskHandle);
  xTaskCreate(greenLedControllerTask, "greenLED",100,NULL,1,&greenTaskHandle);
  xTaskCreate(blueLedControllerTask, "blueLED",100,NULL,1,&blueTaskHandle);
  xTaskCreate(whiteLedControllerTask, "whiteLED",100,NULL,1,&whiteTaskHandle);
  xTaskCreate(redLedControllerTask, "redLED",100,NULL,1,&redTaskHandle);
}
void yellowLedControllerTask(void *pvParameters){
  pinMode(YELLOW, OUTPUT);
  while(1){
    TOGGLE(YELLOW);
    Serial.println("yellow controller Task");
    taskYIELD();
    // delay(300);    
  }
}
void greenLedControllerTask(void *pvParameters){
  pinMode(GREEN, OUTPUT);
  while(1){
    TOGGLE(GREEN);
    vTaskPrioritySet(blueTaskHandle,2);
    // Serial.println(uxTaskPriorityGet(greenTaskHandle));
    // delay(300);
    Serial.println("green controller Task");
    taskYIELD();
  }
}
void blueLedControllerTask(void *pvParameters){
  pinMode(BLUE, OUTPUT);
  while(1){
    TOGGLE(BLUE);
    // delay(300);
    Serial.println("blue controller Task");
    taskYIELD();
  }
}
void whiteLedControllerTask(void *pvParameters){
  pinMode(WHITE, OUTPUT);
  while(1){
    TOGGLE(WHITE);
    // delay(300);
    Serial.println("white controller Task");
    taskYIELD();
  }
}
void redLedControllerTask(void *pvParameters){
  pinMode(RED, OUTPUT);
  while(1){
    TOGGLE(RED);
    // delay(300);
    Serial.println("red controller Task");
    taskYIELD();
  }
}
void loop() {
}
